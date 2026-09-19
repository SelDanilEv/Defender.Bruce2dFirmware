#if !defined(LITE_VERSION)
#include "modules/others/obd_dashboard.h"

#include "core/debug_log.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/sd_functions.h"
#include "core/wifi/wifi_common.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <bitset>
#include <functional>
#include <globals.h>
#include <vector>

static const char *DEFAULT_OBD_HOST = "192.168.0.10";
static const uint16_t DEFAULT_OBD_PORT = 35000;
static const float DEFAULT_CONSUMPTION_L_PER_100 = 8.0f;
static const unsigned long OBD_QUERY_DEADLINE_MS = 1000;
// The ELM327 defers protocol auto-search to the first data query after ATSP0, so that query
// (and the first one after any reconnect) needs a much longer deadline than steady-state polls.
static const unsigned long OBD_FIRST_QUERY_DEADLINE_MS = 8000;
static const unsigned long OBD_RESET_DEADLINE_MS = 2000;
static const unsigned long OBD_INPUT_POLL_MS = 20;
static const unsigned long OBD_FAST_INTERVAL_MS = 500;
static const unsigned long OBD_SLOW_INTERVAL_MS = 5000;
static const unsigned long OBD_FUEL_RETRY_INTERVAL_MS = 5000;
static const unsigned long OBD_FUEL_INTERVAL_MS = 60000;
static const char *OBD_LOG_MODULE = "obd";

namespace {

// ELM327 replies end with a '>' prompt; some adapters split the reply across
// several TCP reads, so bytes are accumulated until the prompt shows up or the deadline expires.
// A millis() deadline is used instead of client.readString()/readStringUntil(), whose blocking
// behavior is bound by the stream timeout (see client.setTimeout below), not by this deadline.
String sendAndDrain(WiFiClient &client, const String &cmd, unsigned long deadlineMs = OBD_QUERY_DEADLINE_MS) {
    // A stale reply from a previous timed-out command must not be misread as this one's reply.
    if (client.available()) {
        String stale;
        while (client.available()) {
            int c = client.read();
            if (c == -1) break;
            stale += (char)c;
        }
        if (stale.length() > 0) DebugLog::write(OBD_LOG_MODULE, "RX", "stale " + stale);
    }

    DebugLog::write(OBD_LOG_MODULE, "TX", cmd);
    client.print(cmd);
    client.print("\r");

    String reply;
    unsigned long deadline = millis() + deadlineMs;
    while (millis() < deadline) {
        while (client.available() && millis() < deadline) {
            int c = client.read();
            if (c == -1) break;
            reply += (char)c;
            if (c == '>') {
                DebugLog::write(OBD_LOG_MODULE, "RX", reply);
                return reply;
            }
        }
        delay(10);
    }
    DebugLog::write(OBD_LOG_MODULE, "RX", reply);
    return reply;
}

String stripFrameChars(const String &raw) {
    String stripped;
    stripped.reserve(raw.length());
    for (size_t i = 0; i < raw.length(); i++) {
        char ch = raw[i];
        if (ch != ' ' && ch != '\r' && ch != '\n') stripped += ch;
    }
    return stripped;
}

bool isPidUnsupported(const String &reply) {
    return reply.indexOf("NODATA") != -1 || reply.indexOf("UNABLE") != -1 || reply.indexOf("STOPPED") != -1 ||
           reply.indexOf("?") != -1;
}

enum ConsumptionSource { SRC_FR, SRC_MAF, SRC_DEF };

// Shared shape for the 1-data-byte, A*100/255 percent PIDs (engine load 0104, throttle 0111
// and its alternates 0145/0147/0149/014C).
bool queryPercentPid(
    WiFiClient &client, const String &cmd, const String &replyTag, float &outPercent, String &rawReplyOut,
    unsigned long deadlineMs = OBD_QUERY_DEADLINE_MS
) {
    rawReplyOut = stripFrameChars(sendAndDrain(client, cmd, deadlineMs));
    int idx = rawReplyOut.indexOf(replyTag);
    if (isPidUnsupported(rawReplyOut) || idx == -1) return false;
    String byteHex = rawReplyOut.substring(idx + replyTag.length(), idx + replyTag.length() + 2);
    outPercent = strtol(byteHex.c_str(), nullptr, 16) * 100.0f / 255.0f;
    return true;
}

// Shared shape for 2-data-byte PIDs (absolute load 0143, RPM 010C, fuel rate 015E, MAF 0110);
// callers apply their own PID-specific formula to the combined A*256+B value.
bool query2ByteValue(
    WiFiClient &client, const String &cmd, const String &replyTag, long &outAB,
    unsigned long deadlineMs = OBD_QUERY_DEADLINE_MS
) {
    String raw = stripFrameChars(sendAndDrain(client, cmd, deadlineMs));
    int idx = raw.indexOf(replyTag);
    if (isPidUnsupported(raw) || idx == -1) return false;
    String a = raw.substring(idx + replyTag.length(), idx + replyTag.length() + 2);
    String b = raw.substring(idx + replyTag.length() + 2, idx + replyTag.length() + 4);
    long A = strtol(a.c_str(), nullptr, 16);
    long B = strtol(b.c_str(), nullptr, 16);
    outAB = A * 256 + B;
    return true;
}

// Shared shape for 1-data-byte raw (non-percent) PIDs (speed 010D).
bool query1ByteRaw(
    WiFiClient &client, const String &cmd, const String &replyTag, long &outA,
    unsigned long deadlineMs = OBD_QUERY_DEADLINE_MS
) {
    String raw = stripFrameChars(sendAndDrain(client, cmd, deadlineMs));
    int idx = raw.indexOf(replyTag);
    if (isPidUnsupported(raw) || idx == -1) return false;
    String a = raw.substring(idx + replyTag.length(), idx + replyTag.length() + 2);
    outA = strtol(a.c_str(), nullptr, 16);
    return true;
}

// ATRV replies with the raw voltage text (e.g. "12.6V") before the '>' prompt.
bool parseBatteryVoltage(const String &reply, float &outVolts) {
    int vIdx = reply.indexOf('V');
    if (vIdx <= 0) return false;
    int start = vIdx;
    while (start > 0 && (isDigit(reply[start - 1]) || reply[start - 1] == '.')) start--;
    if (start == vIdx) return false;
    float v = reply.substring(start, vIdx).toFloat();
    if (v < 5.0f || v > 20.0f) return false;
    outVolts = v;
    return true;
}

enum PidSupportState { PID_SUPPORTED, PID_UNSUPPORTED, PID_UNKNOWN };

// Supported-PID bitmaps from 0100/0120/0140 (PIDs 0x01-0x60). A bitmap query that itself
// fails leaves its whole range PID_UNKNOWN, so callers still probe those PIDs (AC2/AC4).
struct PidSupport {
    std::bitset<0x61> supported;
    std::bitset<3> known;

    PidSupportState state(uint8_t pid) const {
        if (pid == 0 || pid > 0x60) return PID_UNKNOWN;
        int group = (pid - 1) / 0x20;
        if (!known[group]) return PID_UNKNOWN;
        return supported[pid] ? PID_SUPPORTED : PID_UNSUPPORTED;
    }
};

String rangeLabel(int base) {
    char buf[12];
    snprintf(buf, sizeof(buf), "%02X-%02X", base + 1, base + 0x20);
    return String(buf);
}

void probeSupportBitmap(
    WiFiClient &client, const String &cmd, const String &tag, int base, int group, PidSupport &out,
    unsigned long deadlineMs
) {
    String raw = stripFrameChars(sendAndDrain(client, cmd, deadlineMs));
    int idx = raw.indexOf(tag);
    if (isPidUnsupported(raw) || idx == -1 || (int)raw.length() < idx + (int)tag.length() + 8) {
        DebugLog::write(
            OBD_LOG_MODULE, "INFO", "supported " + rangeLabel(base) + ": query failed, treated as unknown"
        );
        return;
    }

    String hexBytes = raw.substring(idx + tag.length(), idx + tag.length() + 8);
    String list;
    for (int i = 0; i < 32; i++) {
        int byteIdx = i / 8;
        int bitInByte = 7 - (i % 8);
        long byteVal = strtol(hexBytes.substring(byteIdx * 2, byteIdx * 2 + 2).c_str(), nullptr, 16);
        int pid = base + i + 1;
        if (((byteVal >> bitInByte) & 1) && pid <= 0x60) {
            out.supported.set(pid);
            char buf[3];
            snprintf(buf, sizeof(buf), "%02X", pid);
            if (list.length() > 0) list += ",";
            list += buf;
        }
    }
    out.known.set(group);
    DebugLog::write(
        OBD_LOG_MODULE,
        "INFO",
        "supported " + rangeLabel(base) + ": " + (list.length() ? list : String("none"))
    );
}

struct ThrottleMethod {
    const char *cmd;
    const char *tag;
    uint8_t pid;
    const char *shortTag;
};

// Priority order: first supported method with a valid reading drives the display.
const ThrottleMethod kThrottleMethods[5] = {
    {"0111", "4111", 0x11, "11"},
    {"0145", "4145", 0x45, "45"},
    {"0147", "4147", 0x47, "47"},
    {"0149", "4149", 0x49, "49"},
    {"014C", "414C", 0x4C, "4C"},
};

struct PollTask {
    const char *name;
    unsigned long intervalMs;
    unsigned long nextDueMs;
    std::function<void()> run;
};

} // namespace

void obd_dashboard_setup() {
    if (!ensureWifiConnected("WiFi not connected")) return;

    String obdHost = num_keyboard(DEFAULT_OBD_HOST, 15, "OBD dongle IP:");
    if (obdHost == "\x1B") return;
    String obdPortStr = num_keyboard(String(DEFAULT_OBD_PORT), 5, "OBD dongle port:");
    if (obdPortStr == "\x1B") return;
    uint16_t obdPort = (uint16_t)atoi(obdPortStr.c_str());
    if (obdHost.length() == 0 || obdPort == 0) obdPort = DEFAULT_OBD_PORT;
    if (obdHost.length() == 0) obdHost = DEFAULT_OBD_HOST;
    String hostPort = obdHost + ":" + String(obdPort);

    WiFiClient client;
    client.setTimeout(1); // seconds; actual bound is the millis() deadline in sendAndDrain
    if (!client.connect(obdHost.c_str(), obdPort)) {
        DebugLog::write(OBD_LOG_MODULE, "INFO", "connect failed: " + hostPort);
        displayError("OBD connect failed: " + hostPort);
        return;
    }

    // Set once after ATSP0/reconnect and consumed by the next sendAndDrain call, so that one
    // query gets the long deadline needed for the ELM327's protocol auto-search.
    bool pendingLongDeadline = true;
    auto nextDeadline = [&]() -> unsigned long {
        if (pendingLongDeadline) {
            pendingLongDeadline = false;
            return OBD_FIRST_QUERY_DEADLINE_MS;
        }
        return OBD_QUERY_DEADLINE_MS;
    };

    auto initAdapter = [&]() {
        sendAndDrain(client, "ATZ", OBD_RESET_DEADLINE_MS);
        sendAndDrain(client, "ATE0");
        sendAndDrain(client, "ATL0");
        sendAndDrain(client, "ATH0");
        sendAndDrain(client, "ATS0");
        sendAndDrain(client, "ATSP0");
        pendingLongDeadline = true;
    };
    initAdapter();

    PidSupport pidSupport;

    float tankL = 50.0f;
    float lPer100 = DEFAULT_CONSUMPTION_L_PER_100;
    float defaultLPer100 = DEFAULT_CONSUMPTION_L_PER_100;
    bool forceDefault = false;
    bool exitToMain = false;

    // Last known-good tank level. Kept across reads so a single bad/split reply
    // does not wipe the value already shown; only a fresh valid reading updates it.
    bool haveLevel = false;
    float lastPercent = 0.0f;
    float lastLiters = 0.0f;
    unsigned long lastLevelUpdateMs = 0;
    ConsumptionSource lastSource = SRC_DEF;
    long lastSpeedKmh = 0;
    bool lastSpeedOk = false;

    // Last known-good live readings. Same keep-last-good pattern as haveLevel/lastPercent:
    // a bad/NO DATA reply for one value never clears the others.
    bool haveLoad = false;
    float lastLoad = 0.0f;
    bool haveThrottle = false;
    float lastThrottle = 0.0f;
    const char *lastThrottleTag = kThrottleMethods[0].shortTag;
    bool haveBatt = false;
    float lastBatt = 0.0f;

    // Health of the adapter link, independent of whether PID 012F has data.
    bool everQueried = false;
    bool adapterResponding = false;

    auto ensureConnected = [&]() -> bool {
        if (client.connected()) return true;
        client.stop();
        if (!client.connect(obdHost.c_str(), obdPort)) {
            adapterResponding = false;
            return false;
        }
        initAdapter();
        return true;
    };

    // --- Startup probing (AC2): adapter id, protocol, supported-PID bitmaps, fuel type. ---
    // ATI/ATDPN are adapter-level, not OBD data queries, so they keep the normal deadline;
    // the long one is reserved for 0100, the first real data query after ATSP0.
    sendAndDrain(client, "ATI");
    sendAndDrain(client, "ATDPN");
    probeSupportBitmap(client, "0100", "4100", 0x00, 0, pidSupport, nextDeadline());
    probeSupportBitmap(client, "0120", "4120", 0x20, 1, pidSupport, OBD_QUERY_DEADLINE_MS);
    probeSupportBitmap(client, "0140", "4140", 0x40, 2, pidSupport, OBD_QUERY_DEADLINE_MS);
    sendAndDrain(client, "0151"); // fuel type, logged raw only per AC4

    int activeThrottleIdx = 0;
    for (int i = 0; i < 5; i++) {
        if (pidSupport.state(kThrottleMethods[i].pid) != PID_UNSUPPORTED) {
            activeThrottleIdx = i;
            break;
        }
    }
    lastThrottleTag = kThrottleMethods[activeThrottleIdx].shortTag;

    auto openTankMenu = [&]() {
        options = {
            {"Set tank size",
             [&]() {
                 String s = num_keyboard(String((int)tankL), 4, "Tank size (L):");
                 float v = s.toFloat();
                 if (v > 0) tankL = v;
             }                                                                                              },
            {"Set consumption",
             [&]() {
                 String s = num_keyboard(String(defaultLPer100, 1), 4, "Cons L/100km:");
                 float v = s.toFloat();
                 if (v > 0) defaultLPer100 = v;
             }                                                                                              },
            {String(forceDefault ? "Force default: ON" : "Force default: OFF"),
             [&]() { forceDefault = !forceDefault; }                                                        },
            {"Back",                                                            []() {}                     },
            {"Main menu",                                                       [&]() { exitToMain = true; }},
        };
        loopOptions(options, MENU_TYPE_SUBMENU, "OBD Dashboard");
    };

    // --- Fast group (~500ms): the values actually shown, plus RPM so the log can tell an
    // engine-off reading (load 0%, RPM 0) apart from a sensor fault. ---
    auto pollLoadPrimary = [&]() {
        everQueried = true;
        if (!ensureConnected()) return;
        float pct;
        String raw;
        bool ok = queryPercentPid(client, "0104", "4104", pct, raw, nextDeadline());
        adapterResponding = raw.length() > 0;
        DebugLog::write(
            OBD_LOG_MODULE, "INFO", "val load 0104 " + (ok ? String((int)pct) + "%" : String("NA"))
        );
        if (ok) {
            lastLoad = pct;
            haveLoad = true;
        }
    };

    auto pollThrottleActive = [&]() {
        if (!ensureConnected()) return;
        const ThrottleMethod &m = kThrottleMethods[activeThrottleIdx];
        float pct;
        String raw;
        bool ok = queryPercentPid(client, m.cmd, m.tag, pct, raw, nextDeadline());
        DebugLog::write(
            OBD_LOG_MODULE,
            "INFO",
            String("val throttle ") + m.cmd + " " + (ok ? String((int)pct) + "%" : String("NA"))
        );
        if (ok) {
            lastThrottle = pct;
            lastThrottleTag = m.shortTag;
            haveThrottle = true;
        }
    };

    auto pollRpm = [&]() {
        if (!ensureConnected()) return;
        long ab;
        bool ok = query2ByteValue(client, "010C", "410C", ab, nextDeadline());
        DebugLog::write(OBD_LOG_MODULE, "INFO", "val rpm 010C " + (ok ? String(ab / 4) : String("NA")));
    };

    // --- Slow group (~5s): alternate/unused probe methods, logged for reference only. ---
    auto pollLoadAlt = [&]() {
        if (!ensureConnected()) return;
        long ab;
        bool ok = query2ByteValue(client, "0143", "4143", ab, nextDeadline());
        String val = ok ? String(ab * 100.0f / 255.0f, 0) + "%" : String("NA");
        DebugLog::write(OBD_LOG_MODULE, "INFO", "val load 0143 " + val);
    };

    auto pollThrottleAlt = [&](int idx) {
        if (!ensureConnected()) return;
        const ThrottleMethod &m = kThrottleMethods[idx];
        if (pidSupport.state(m.pid) == PID_UNSUPPORTED) {
            DebugLog::write(OBD_LOG_MODULE, "INFO", String("val throttle ") + m.cmd + " NA");
            return;
        }
        float pct;
        String raw;
        bool ok = queryPercentPid(client, m.cmd, m.tag, pct, raw, nextDeadline());
        DebugLog::write(
            OBD_LOG_MODULE,
            "INFO",
            String("val throttle ") + m.cmd + " " + (ok ? String((int)pct) + "%" : String("NA"))
        );
    };

    auto pollBattery = [&]() {
        if (!ensureConnected()) return;
        String rvReply = sendAndDrain(client, "ATRV", nextDeadline());
        float volts;
        bool ok = parseBatteryVoltage(rvReply, volts);
        DebugLog::write(
            OBD_LOG_MODULE, "INFO", "val battery ATRV " + (ok ? String(volts, 1) + "V" : String("NA"))
        );
        if (ok) {
            lastBatt = volts;
            haveBatt = true;
        }
    };

    // --- Fuel group: 5s until the first valid reading, then 60s (tank level changes slowly). ---
    auto pollFuelLevel = [&]() {
        if (!ensureConnected()) return;
        String reply = stripFrameChars(sendAndDrain(client, "012F", nextDeadline()));
        adapterResponding = reply.length() > 0;
        int pidIndex = reply.indexOf("412F");
        bool levelValid = !isPidUnsupported(reply) && pidIndex != -1;
        if (levelValid) {
            String byteHex = reply.substring(pidIndex + 4, pidIndex + 6);
            long a = strtol(byteHex.c_str(), nullptr, 16);
            lastPercent = a * 100.0f / 255.0f;
            lastLiters = lastPercent / 100.0f * tankL;
            lastLevelUpdateMs = millis();
            haveLevel = true;
            DebugLog::write(OBD_LOG_MODULE, "INFO", "val fuel 012F " + String((int)lastPercent) + "%");
        } else {
            DebugLog::write(OBD_LOG_MODULE, "INFO", "val fuel 012F NA");
        }
    };

    auto pollFuelSpeed = [&]() {
        if (!ensureConnected()) return;
        long a;
        lastSpeedOk = query1ByteRaw(client, "010D", "410D", a, nextDeadline());
        lastSpeedKmh = lastSpeedOk ? a : 0;
        DebugLog::write(
            OBD_LOG_MODULE,
            "INFO",
            "val speed 010D " + (lastSpeedOk ? String(lastSpeedKmh) + "km/h" : String("NA"))
        );
    };

    auto pollFuelRate = [&]() {
        if (!ensureConnected()) return;
        long ab;
        bool frOk = query2ByteValue(client, "015E", "415E", ab, nextDeadline());
        float fuelRateLh = 0.0f;
        ConsumptionSource source = SRC_DEF;
        if (frOk) {
            fuelRateLh = ab / 20.0f;
            source = SRC_FR;
            DebugLog::write(OBD_LOG_MODULE, "INFO", "val fuelrate 015E " + String(fuelRateLh, 1) + "L/h");
        } else {
            DebugLog::write(OBD_LOG_MODULE, "INFO", "val fuelrate 015E NA");
            long mafAb;
            // MAF (0110, g/s) fallback, converted for gasoline: stoich AFR 14.7:1, 745 g/L density.
            bool mafOk = query2ByteValue(client, "0110", "4110", mafAb, nextDeadline());
            if (mafOk) {
                float mafGs = mafAb / 100.0f;
                fuelRateLh = mafGs * 3600.0f / (14.7f * 745.0f);
                source = SRC_MAF;
                DebugLog::write(OBD_LOG_MODULE, "INFO", "val maf 0110 " + String(mafGs, 1) + "g/s");
            } else {
                DebugLog::write(OBD_LOG_MODULE, "INFO", "val maf 0110 NA");
            }
        }

        if (forceDefault || source == SRC_DEF) {
            lPer100 = defaultLPer100;
        } else if (lastSpeedOk && lastSpeedKmh >= 3) {
            float inst = fuelRateLh / lastSpeedKmh * 100.0f;
            if (inst >= 0.0f && inst <= 60.0f) lPer100 = 0.8f * lPer100 + 0.2f * inst;
        }
        lastSource = source;
    };

    auto draw = [&]() {
        String health = !everQueried ? "[...]" : (adapterResponding ? "[OK]" : "[NO RESP]");
        const char *srcTag = lastSource == SRC_FR ? "FR" : lastSource == SRC_MAF ? "MAF" : "def";
        if (forceDefault) srcTag = "def";

        String subtitle = "OBD " + health;
#ifdef BRUCE_DEBUG_LOG
        subtitle += String("  Log: ") + (DebugLog::active() ? "SD" : "no SD");
#endif
        if (haveLevel) subtitle += " " + String((millis() - lastLevelUpdateMs) / 1000) + "s ago";

        drawMainBorder();
        printSubtitle(subtitle);
        if (haveLevel) {
            float missing = tankL - lastLiters;
            if (missing < 0.0f) missing = 0.0f;
            float rangeKm = lastLiters / (lPer100 / 100.0f);
            padprintln("Level: " + String((int)lastPercent) + "%");
            padprintln("Fuel: " + String(lastLiters, 1) + " L");
            padprintln("Missing: " + String(missing, 1) + " L");
            padprintln("Range: " + String((int)rangeKm) + " km");
        } else if (pidSupport.state(0x2F) == PID_UNSUPPORTED) {
            padprintln("Level: n/s");
        } else {
            padprintln("Level: --");
        }
        padprintln("Cons: " + String(lPer100, 1) + " L/100km (" + srcTag + ")");
        String loadStr = haveLoad ? String((int)lastLoad) + "%" : String("--");
        String thrStr =
            haveThrottle ? String((int)lastThrottle) + "% (" + lastThrottleTag + ")" : String("--");
        String battStr = haveBatt ? String(lastBatt, 1) + " V" : String("--");
        padprintln("Load: " + loadStr + "  Thr: " + thrStr);
        padprintln("Batt: " + battStr);
        padprintln("[scroll] menu  [Esc] exit");
    };

    std::vector<PollTask> tasks = {
        {"load",     OBD_FAST_INTERVAL_MS,       0, pollLoadPrimary   },
        {"throttle", OBD_FAST_INTERVAL_MS,       0, pollThrottleActive},
        {"rpm",      OBD_FAST_INTERVAL_MS,       0, pollRpm           },
        {"loadAlt",  OBD_SLOW_INTERVAL_MS,       0, pollLoadAlt       },
        {"battery",  OBD_SLOW_INTERVAL_MS,       0, pollBattery       },
        {"fuelLvl",  OBD_FUEL_RETRY_INTERVAL_MS, 0, pollFuelLevel     },
        {"fuelSpd",  OBD_FUEL_RETRY_INTERVAL_MS, 0, pollFuelSpeed     },
        {"fuelRate", OBD_FUEL_RETRY_INTERVAL_MS, 0, pollFuelRate      },
    };
    for (int i = 0; i < 5; i++) {
        if (i == activeThrottleIdx) continue;
        tasks.push_back({"throttleAlt", OBD_SLOW_INTERVAL_MS, 0, [&pollThrottleAlt, i]() {
                             pollThrottleAlt(i);
                         }});
    }

    draw();
    unsigned long lastDrawMs = millis();

    while (!exitToMain && !check(EscPress)) {
        if (check(NextPress) || check(PrevPress)) {
            openTankMenu();
            draw();
            lastDrawMs = millis();
            continue;
        }

        unsigned long now = millis();
        bool ranOne = false;
        for (auto &task : tasks) {
            if (now >= task.nextDueMs) {
                task.run();
                task.nextDueMs = millis() + task.intervalMs;
                if (haveLevel && task.intervalMs == OBD_FUEL_RETRY_INTERVAL_MS)
                    task.intervalMs = OBD_FUEL_INTERVAL_MS;

                // Flush once per query (not per log line) so data survives a power cut
                // without hammering flash on every byte written.
                DebugLog::flush(OBD_LOG_MODULE);

                draw();
                lastDrawMs = millis();
                ranOne = true;
                break;
            }
        }

        if (check(EscPress)) break;

        if (!ranOne && now - lastDrawMs >= 1000) {
            // Redraw once a second so the "Ns ago" counter in the subtitle keeps ticking.
            draw();
            lastDrawMs = millis();
        }

        delay(OBD_INPUT_POLL_MS);
    }

    client.stop();
}

#endif // LITE_VERSION
