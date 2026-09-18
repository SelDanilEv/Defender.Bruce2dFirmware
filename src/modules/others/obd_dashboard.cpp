#if !defined(LITE_VERSION)
#include "modules/others/obd_dashboard.h"

#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/wifi/wifi_common.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <globals.h>

static const char *DEFAULT_OBD_HOST = "192.168.0.10";
static const uint16_t DEFAULT_OBD_PORT = 35000;
static const float DEFAULT_CONSUMPTION_L_PER_100 = 8.0f;
static const unsigned long OBD_QUERY_DEADLINE_MS = 1000;
// Fuel level changes slowly, so the tank is only polled once per minute. Between
// polls the loop stays free to react to input, which keeps the UI responsive.
static const unsigned long OBD_REFRESH_INTERVAL_MS = 60000;
// Engine load, throttle and battery voltage change quickly, so they get their own faster poll.
static const unsigned long OBD_LIVE_REFRESH_INTERVAL_MS = 3000;
static const unsigned long OBD_INPUT_POLL_MS = 20;

namespace {

// ELM327 replies end with a '>' prompt; some adapters split the reply across
// several TCP reads, so bytes are accumulated until the prompt shows up or the deadline expires.
// A millis() deadline is used instead of client.readString()/readStringUntil(), whose blocking
// behavior is bound by the stream timeout (see client.setTimeout below), not by this deadline.
String sendAndDrain(WiFiClient &client, const String &cmd) {
    client.print(cmd);
    client.print("\r");

    String reply;
    unsigned long deadline = millis() + OBD_QUERY_DEADLINE_MS;
    while (millis() < deadline) {
        while (client.available() && millis() < deadline) {
            int c = client.read();
            if (c == -1) break;
            reply += (char)c;
            if (c == '>') return reply;
        }
        delay(10);
    }
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

// Shared shape for the 1-data-byte, A*100/255 percent PIDs (engine load 0104, throttle 0111).
// rawReplyOut is the stripped reply so callers can tell an empty (no answer) reply from an
// unsupported-PID one, without querying twice.
bool queryPercentPid(
    WiFiClient &client, const String &cmd, const String &replyTag, float &outPercent, String &rawReplyOut
) {
    rawReplyOut = stripFrameChars(sendAndDrain(client, cmd));
    int idx = rawReplyOut.indexOf(replyTag);
    if (isPidUnsupported(rawReplyOut) || idx == -1) return false;
    String byteHex = rawReplyOut.substring(idx + replyTag.length(), idx + replyTag.length() + 2);
    outPercent = strtol(byteHex.c_str(), nullptr, 16) * 100.0f / 255.0f;
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
        displayError("OBD connect failed: " + hostPort);
        return;
    }

    auto initAdapter = [&]() {
        sendAndDrain(client, "ATZ");
        sendAndDrain(client, "ATE0");
        sendAndDrain(client, "ATSP0");
    };
    initAdapter();

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

    // Last known-good live readings. Same keep-last-good pattern as haveLevel/lastPercent:
    // a bad/NO DATA reply for one value never clears the others.
    bool haveLoad = false;
    float lastLoad = 0.0f;
    bool haveThrottle = false;
    float lastThrottle = 0.0f;
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

    auto doRefresh = [&]() {
        everQueried = true;

        if (!ensureConnected()) return;

        String reply = stripFrameChars(sendAndDrain(client, "012F"));
        // The adapter is healthy if it answered at all, even with NO DATA for this PID.
        adapterResponding = reply.length() > 0;

        int pidIndex = reply.indexOf("412F");
        bool levelValid = !isPidUnsupported(reply) && pidIndex != -1;

        // Speed (010D -> 410D, 1 data byte, km/h) gates instantaneous consumption below.
        String speedReply = stripFrameChars(sendAndDrain(client, "010D"));
        int speedIdx = speedReply.indexOf("410D");
        bool speedOk = !isPidUnsupported(speedReply) && speedIdx != -1;
        int speedKmh = 0;
        if (speedOk) {
            String a = speedReply.substring(speedIdx + 4, speedIdx + 6);
            speedKmh = strtol(a.c_str(), nullptr, 16);
        }

        // Fuel rate (015E -> 415E, 2 data bytes) is the preferred consumption source.
        String frReply = stripFrameChars(sendAndDrain(client, "015E"));
        int frIdx = frReply.indexOf("415E");
        bool frOk = !isPidUnsupported(frReply) && frIdx != -1;
        float fuelRateLh = 0.0f;
        ConsumptionSource source = SRC_DEF;
        if (frOk) {
            String a = frReply.substring(frIdx + 4, frIdx + 6);
            String b = frReply.substring(frIdx + 6, frIdx + 8);
            long A = strtol(a.c_str(), nullptr, 16);
            long B = strtol(b.c_str(), nullptr, 16);
            fuelRateLh = (A * 256 + B) / 20.0f;
            source = SRC_FR;
        } else {
            // MAF (0110 -> 4110, 2 data bytes, g/s) fallback, converted for gasoline:
            // stoich AFR 14.7:1 and 745 g/L density.
            String mafReply = stripFrameChars(sendAndDrain(client, "0110"));
            int mafIdx = mafReply.indexOf("4110");
            bool mafOk = !isPidUnsupported(mafReply) && mafIdx != -1;
            if (mafOk) {
                String a = mafReply.substring(mafIdx + 4, mafIdx + 6);
                String b = mafReply.substring(mafIdx + 6, mafIdx + 8);
                long A = strtol(a.c_str(), nullptr, 16);
                long B = strtol(b.c_str(), nullptr, 16);
                float mafGs = (A * 256 + B) / 100.0f;
                fuelRateLh = mafGs * 3600.0f / (14.7f * 745.0f);
                source = SRC_MAF;
            }
        }

        if (forceDefault || source == SRC_DEF) {
            lPer100 = defaultLPer100;
        } else if (speedOk && speedKmh >= 3) {
            float inst = fuelRateLh / speedKmh * 100.0f;
            if (inst >= 0.0f && inst <= 60.0f) lPer100 = 0.8f * lPer100 + 0.2f * inst;
        }
        lastSource = source;

        if (levelValid) {
            String byteHex = reply.substring(pidIndex + 4, pidIndex + 6);
            long a = strtol(byteHex.c_str(), nullptr, 16);
            lastPercent = a * 100.0f / 255.0f;
            lastLiters = lastPercent / 100.0f * tankL;
            lastLevelUpdateMs = millis();
            haveLevel = true;
        }
    };

    auto doLiveRefresh = [&]() {
        if (!ensureConnected()) return;

        String rawReply;
        float pct;
        if (queryPercentPid(client, "0104", "4104", pct, rawReply)) {
            lastLoad = pct;
            haveLoad = true;
        }
        // The adapter is healthy if it answered at all, even with NO DATA for this PID.
        adapterResponding = rawReply.length() > 0;

        if (queryPercentPid(client, "0111", "4111", pct, rawReply)) {
            lastThrottle = pct;
            haveThrottle = true;
        }

        String rvReply = sendAndDrain(client, "ATRV");
        float volts;
        if (parseBatteryVoltage(rvReply, volts)) {
            lastBatt = volts;
            haveBatt = true;
        }
    };

    auto draw = [&]() {
        String health = !everQueried ? "[...]" : (adapterResponding ? "[OK]" : "[NO RESP]");
        const char *srcTag = lastSource == SRC_FR ? "FR" : lastSource == SRC_MAF ? "MAF" : "def";
        if (forceDefault) srcTag = "def";

        String subtitle = "OBD " + health;
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
        } else {
            padprintln("Level: --");
        }
        padprintln("Cons: " + String(lPer100, 1) + " L/100km (" + srcTag + ")");
        String loadStr = haveLoad ? String((int)lastLoad) + "%" : String("--");
        String thrStr = haveThrottle ? String((int)lastThrottle) + "%" : String("--");
        String battStr = haveBatt ? String(lastBatt, 1) + " V" : String("--");
        padprintln("Load: " + loadStr + "  Thr: " + thrStr);
        padprintln("Batt: " + battStr);
        padprintln("[scroll] menu  [Esc] exit");
    };

    doRefresh();
    unsigned long lastRefreshMs = millis();
    doLiveRefresh();
    unsigned long lastLiveRefreshMs = millis();
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
        if (now - lastRefreshMs >= OBD_REFRESH_INTERVAL_MS) {
            doRefresh();
            lastRefreshMs = millis();
            draw();
            lastDrawMs = millis();
        } else if (now - lastLiveRefreshMs >= OBD_LIVE_REFRESH_INTERVAL_MS) {
            doLiveRefresh();
            lastLiveRefreshMs = millis();
            draw();
            lastDrawMs = millis();
        } else if (now - lastDrawMs >= 1000) {
            // Redraw once a second so the "Ns ago" counter in the subtitle keeps ticking.
            draw();
            lastDrawMs = millis();
        }

        delay(OBD_INPUT_POLL_MS);
    }

    client.stop();
}

#endif // LITE_VERSION
