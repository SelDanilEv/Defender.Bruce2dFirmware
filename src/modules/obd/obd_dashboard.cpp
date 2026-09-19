#if !defined(LITE_VERSION)
#include "modules/obd/obd_dashboard.h"

#include "core/debug_log.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/wifi/wifi_common.h"
#include "modules/obd/elm327_client.h"
#include "modules/obd/obd_pids.h"
#include "modules/obd/obd_poll_scheduler.h"

#include <Preferences.h>
#include <bitset>
#include <globals.h>

namespace {

const char *DEFAULT_OBD_HOST = "192.168.0.10";
const uint16_t DEFAULT_OBD_PORT = 35000;
const long MAX_TCP_PORT = 65535;
const float DEFAULT_TANK_L = 50.0f;
const char *TANK_SIZE_NS = "obd";
const char *TANK_SIZE_KEY = "tankL";
const float DEFAULT_CONSUMPTION_L_PER_100 = 8.0f;
const unsigned long OBD_INPUT_POLL_MS = 20;
const unsigned long OBD_REDRAW_INTERVAL_MS = 1000;
const unsigned long MS_PER_SECOND = 1000;
const uint32_t OBD_FAST_INTERVAL_MS = 500;
const uint32_t OBD_SLOW_INTERVAL_MS = 5000;
const uint32_t OBD_CONSUMPTION_INTERVAL_MS = 5000;
const uint32_t OBD_FUEL_RETRY_INTERVAL_MS = 5000;
const uint32_t OBD_FUEL_LEVEL_INTERVAL_MS = 60000;
const uint8_t FUEL_LEVEL_PID = 0x2F;
const int PIDS_PER_SUPPORT_GROUP = 0x20;
const int SUPPORT_GROUP_COUNT = 3;
const int MAX_TRACKED_PID = PIDS_PER_SUPPORT_GROUP * SUPPORT_GROUP_COUNT;

enum ConsumptionSource { SRC_FR, SRC_MAF, SRC_DEF };

enum PidSupportState { PID_SUPPORTED, PID_UNSUPPORTED, PID_UNKNOWN };

// A bitmap query that fails leaves its whole range unknown, so those PIDs are still probed.
struct PidSupport {
    std::bitset<MAX_TRACKED_PID + 1> supported;
    std::bitset<SUPPORT_GROUP_COUNT> known;

    PidSupportState state(uint8_t pid) const {
        if (pid == 0 || pid > MAX_TRACKED_PID) return PID_UNKNOWN;
        int group = (pid - 1) / PIDS_PER_SUPPORT_GROUP;
        if (!known[group]) return PID_UNKNOWN;
        return supported[pid] ? PID_SUPPORTED : PID_UNSUPPORTED;
    }
};

struct ThrottleMethod {
    const char *cmd;
    const char *tag;
    uint8_t pid;
    const char *shortTag;
};

// Priority order: first supported method drives the display.
const ThrottleMethod THROTTLE_METHODS[] = {
    {"0111", "4111", 0x11, "11"},
    {"0145", "4145", 0x45, "45"},
    {"0147", "4147", 0x47, "47"},
    {"0149", "4149", 0x49, "49"},
    {"014C", "414C", 0x4C, "4C"},
};
const int THROTTLE_METHOD_COUNT = sizeof(THROTTLE_METHODS) / sizeof(THROTTLE_METHODS[0]);

struct Reading {
    bool valid = false;
    float value = 0.0f;

    void set(float newValue) {
        value = newValue;
        valid = true;
    }
};

struct ObdDashboard;
using PollFn = void (*)(ObdDashboard &, int);

struct TaskBinding {
    PollFn run = nullptr;
    int arg = 0;
};

float loadTankSize() {
    Preferences prefs;
    if (!prefs.begin(TANK_SIZE_NS, true)) return DEFAULT_TANK_L;
    float value = prefs.getFloat(TANK_SIZE_KEY, DEFAULT_TANK_L);
    prefs.end();
    return value > 0 ? value : DEFAULT_TANK_L;
}

void saveTankSize(float value) {
    Preferences prefs;
    if (!prefs.begin(TANK_SIZE_NS, false)) return;
    prefs.putFloat(TANK_SIZE_KEY, value);
    prefs.end();
}

struct ObdDashboard {
    Elm327Client elm;
    PidSupport pidSupport;
    obd::PollScheduler scheduler;
    TaskBinding tasks[obd::PollScheduler::MAX_TASKS];
    int fuelLevelTask = obd::PollScheduler::NONE_DUE;

    float tankL = DEFAULT_TANK_L;
    float lPer100 = DEFAULT_CONSUMPTION_L_PER_100;
    float defaultLPer100 = DEFAULT_CONSUMPTION_L_PER_100;
    bool forceDefault = false;
    bool exitToMain = false;
    bool menuRequested = false;
    bool everQueried = false;

    // Last known-good values: a bad or NO DATA reply never clears what is already shown.
    bool haveLevel = false;
    float lastPercent = 0.0f;
    float lastLiters = 0.0f;
    unsigned long lastLevelUpdateMs = 0;
    ConsumptionSource lastSource = SRC_DEF;
    Reading load;
    Reading throttle;
    Reading battery;
    int activeThrottleIdx = 0;
    const char *lastThrottleTag = THROTTLE_METHODS[0].shortTag;

    ObdDashboard(const String &host, uint16_t port) : elm(host, port) { tankL = loadTankSize(); }
};

void logInfo(const String &text) { DebugLog::write(OBD_LOG_MODULE, "INFO", text); }

String percentText(bool ok, float percent) { return ok ? String((int)percent) + "%" : String("NA"); }

bool replyPercent(const ElmReply &reply, const char *tag, float &outPercent) {
    return reply.hasData() && obd::decodePercent(reply.raw.c_str(), reply.raw.length(), tag, outPercent);
}

bool reply1Byte(const ElmReply &reply, const char *tag, long &outA) {
    return reply.hasData() && obd::decode1Byte(reply.raw.c_str(), reply.raw.length(), tag, outA);
}

bool reply2Byte(const ElmReply &reply, const char *tag, long &outAB) {
    return reply.hasData() && obd::decode2Byte(reply.raw.c_str(), reply.raw.length(), tag, outAB);
}

String rangeLabel(int base) {
    char buf[12];
    snprintf(buf, sizeof(buf), "%02X-%02X", base + 1, base + PIDS_PER_SUPPORT_GROUP);
    return String(buf);
}

void probeSupportBitmap(ObdDashboard &dash, const char *cmd, const char *tag, int group) {
    const int base = group * PIDS_PER_SUPPORT_GROUP;
    const int bitmapBits = 32;
    ElmReply reply = dash.elm.queryData(cmd, tag);
    uint32_t bits = 0;
    bool ok = reply.hasData() && obd::decodeSupportBitmap(reply.raw.c_str(), reply.raw.length(), tag, bits);
    if (!ok) {
        logInfo("supported " + rangeLabel(base) + ": query failed, treated as unknown");
        return;
    }

    String list;
    for (int i = 0; i < bitmapBits; i++) {
        int pid = base + i + 1;
        bool bitSet = (bits >> (bitmapBits - 1 - i)) & 1;
        if (!bitSet || pid > MAX_TRACKED_PID) continue;
        dash.pidSupport.supported.set(pid);
        char buf[3];
        snprintf(buf, sizeof(buf), "%02X", pid);
        if (list.length() > 0) list += ",";
        list += buf;
    }
    dash.pidSupport.known.set(group);
    logInfo("supported " + rangeLabel(base) + ": " + (list.length() ? list : String("none")));
}

void probeAdapter(ObdDashboard &dash) {
    dash.elm.query("ATI", "", Elm327Client::STEADY_DEADLINE_MS);
    dash.elm.query("ATDPN", "", Elm327Client::STEADY_DEADLINE_MS);
    probeSupportBitmap(dash, "0100", "4100", 0);
    probeSupportBitmap(dash, "0120", "4120", 1);
    probeSupportBitmap(dash, "0140", "4140", 2);
    dash.elm.queryData("0151", "4151");

    for (int i = 0; i < THROTTLE_METHOD_COUNT; i++) {
        if (dash.pidSupport.state(THROTTLE_METHODS[i].pid) != PID_UNSUPPORTED) {
            dash.activeThrottleIdx = i;
            break;
        }
    }
    dash.lastThrottleTag = THROTTLE_METHODS[dash.activeThrottleIdx].shortTag;
}

void pollLoadPrimary(ObdDashboard &dash, int) {
    float percent;
    bool ok = replyPercent(dash.elm.queryData("0104", "4104"), "4104", percent);
    logInfo("val load 0104 " + percentText(ok, percent));
    if (ok) dash.load.set(percent);
}

void queryThrottle(ObdDashboard &dash, int methodIdx, bool drivesDisplay) {
    const ThrottleMethod &method = THROTTLE_METHODS[methodIdx];
    float percent;
    bool ok = replyPercent(dash.elm.queryData(method.cmd, method.tag), method.tag, percent);
    logInfo(String("val throttle ") + method.cmd + " " + percentText(ok, percent));
    if (!ok || !drivesDisplay) return;
    dash.throttle.set(percent);
    dash.lastThrottleTag = method.shortTag;
}

void pollThrottleActive(ObdDashboard &dash, int) { queryThrottle(dash, dash.activeThrottleIdx, true); }

void pollThrottleAlt(ObdDashboard &dash, int methodIdx) {
    const ThrottleMethod &method = THROTTLE_METHODS[methodIdx];
    if (dash.pidSupport.state(method.pid) == PID_UNSUPPORTED) {
        logInfo(String("val throttle ") + method.cmd + " NA");
        return;
    }
    queryThrottle(dash, methodIdx, false);
}

// Logged so an engine-off reading (load 0%, RPM 0) can be told apart from a sensor fault.
void pollRpm(ObdDashboard &dash, int) {
    long ab;
    bool ok = reply2Byte(dash.elm.queryData("010C", "410C"), "410C", ab);
    logInfo("val rpm 010C " + (ok ? String(obd::rpmFromAB(ab)) : String("NA")));
}

void pollLoadAlt(ObdDashboard &dash, int) {
    long ab;
    bool ok = reply2Byte(dash.elm.queryData("0143", "4143"), "4143", ab);
    String value = ok ? String(obd::percentFromByte(ab), 0) + "%" : String("NA");
    logInfo("val load 0143 " + value);
}

void pollBattery(ObdDashboard &dash, int) {
    ElmReply reply = dash.elm.queryData("ATRV", "");
    float volts;
    bool ok = reply.hasData() && obd::parseBatteryVoltage(reply.raw.c_str(), reply.raw.length(), volts);
    logInfo("val battery ATRV " + (ok ? String(volts, 1) + "V" : String("NA")));
    if (ok) dash.battery.set(volts);
}

void pollFuelLevel(ObdDashboard &dash, int) {
    long a;
    if (!reply1Byte(dash.elm.queryData("012F", "412F"), "412F", a)) {
        logInfo("val fuel 012F NA");
        return;
    }
    dash.lastPercent = obd::percentFromByte(a);
    dash.lastLiters = dash.lastPercent / obd::PERCENT_SCALE * dash.tankL;
    dash.lastLevelUpdateMs = millis();
    dash.haveLevel = true;
    logInfo("val fuel 012F " + String((int)dash.lastPercent) + "%");
}

bool pollFuelRateLh(ObdDashboard &dash, float &outRateLh, ConsumptionSource &outSource) {
    long ab;
    if (reply2Byte(dash.elm.queryData("015E", "415E"), "415E", ab)) {
        outRateLh = obd::fuelRateLhFromAB(ab);
        outSource = SRC_FR;
        logInfo("val fuelrate 015E " + String(outRateLh, 1) + "L/h");
        return true;
    }
    logInfo("val fuelrate 015E NA");
    if (reply2Byte(dash.elm.queryData("0110", "4110"), "4110", ab)) {
        float mafGs = obd::mafGsFromAB(ab);
        outRateLh = obd::fuelRateLhFromMaf(mafGs);
        outSource = SRC_MAF;
        logInfo("val maf 0110 " + String(mafGs, 1) + "g/s");
        return true;
    }
    logInfo("val maf 0110 NA");
    return false;
}

void pollConsumption(ObdDashboard &dash, int) {
    obd::ConsumptionSample sample = {false, 0.0f, false, 0};
    sample.speedOk = reply1Byte(dash.elm.queryData("010D", "410D"), "410D", sample.speedKmh);
    if (!sample.speedOk) sample.speedKmh = 0;
    logInfo("val speed 010D " + (sample.speedOk ? String(sample.speedKmh) + "km/h" : String("NA")));

    ConsumptionSource source = SRC_DEF;
    sample.rateOk = pollFuelRateLh(dash, sample.fuelRateLh, source);
    dash.lPer100 = obd::updateConsumption(dash.lPer100, dash.defaultLPer100, dash.forceDefault, sample);
    if (sample.rateOk) dash.lastSource = source;
}

struct PollTaskDef {
    uint32_t intervalMs;
    PollFn run;
};

const PollTaskDef FIXED_TASKS[] = {
    {OBD_FAST_INTERVAL_MS,        pollLoadPrimary   },
    {OBD_FAST_INTERVAL_MS,        pollThrottleActive},
    {OBD_FAST_INTERVAL_MS,        pollRpm           },
    {OBD_SLOW_INTERVAL_MS,        pollLoadAlt       },
    {OBD_SLOW_INTERVAL_MS,        pollBattery       },
    {OBD_FUEL_RETRY_INTERVAL_MS,  pollFuelLevel     },
    {OBD_CONSUMPTION_INTERVAL_MS, pollConsumption   },
};

void addTask(ObdDashboard &dash, uint32_t intervalMs, PollFn run, int arg) {
    int index = dash.scheduler.addTask(intervalMs, millis());
    if (index == obd::PollScheduler::NONE_DUE) return;
    dash.tasks[index] = {run, arg};
    if (run == pollFuelLevel) dash.fuelLevelTask = index;
}

void buildTasks(ObdDashboard &dash) {
    for (const PollTaskDef &task : FIXED_TASKS) addTask(dash, task.intervalMs, task.run, 0);
    for (int i = 0; i < THROTTLE_METHOD_COUNT; i++) {
        if (i != dash.activeThrottleIdx) addTask(dash, OBD_SLOW_INTERVAL_MS, pollThrottleAlt, i);
    }
}

bool runDueTask(ObdDashboard &dash) {
    int index = dash.scheduler.pickMostOverdue(millis());
    if (index == obd::PollScheduler::NONE_DUE) return false;
    dash.everQueried = true;
    if (dash.elm.ensureLink()) dash.tasks[index].run(dash, dash.tasks[index].arg);
    if (index == dash.fuelLevelTask && dash.haveLevel) {
        dash.scheduler.setInterval(index, OBD_FUEL_LEVEL_INTERVAL_MS);
    }
    dash.scheduler.markRan(index, millis());
    // Flush once per query (not per log line) so data survives a power cut without wearing flash.
    DebugLog::flush(OBD_LOG_MODULE);
    return true;
}

void draw(ObdDashboard &dash) {
    String health = !dash.everQueried ? "[...]" : (dash.elm.responding() ? "[OK]" : "[NO RESP]");
    const char *srcTag = dash.lastSource == SRC_FR ? "FR" : dash.lastSource == SRC_MAF ? "MAF" : "def";
    if (dash.forceDefault) srcTag = "def";

    String subtitle = "OBD " + health;
#ifdef BRUCE_DEBUG_LOG
    subtitle += String("  Log: ") + (DebugLog::active() ? "SD" : "no SD");
#endif
    if (dash.haveLevel) {
        subtitle += " " + String((millis() - dash.lastLevelUpdateMs) / MS_PER_SECOND) + "s ago";
    }

    drawMainBorder();
    printSubtitle(subtitle);
    if (dash.haveLevel) {
        float missing = dash.tankL - dash.lastLiters;
        if (missing < 0.0f) missing = 0.0f;
        float rangeKm = dash.lastLiters / (dash.lPer100 / obd::PERCENT_SCALE);
        padprintln("Level: " + String((int)dash.lastPercent) + "%");
        padprintln("Fuel: " + String(dash.lastLiters, 1) + " L");
        padprintln("Missing: " + String(missing, 1) + " L");
        padprintln("Range: " + String((int)rangeKm) + " km");
    } else if (dash.pidSupport.state(FUEL_LEVEL_PID) == PID_UNSUPPORTED) {
        padprintln("Level: n/s");
    } else {
        padprintln("Level: --");
    }
    padprintln("Cons: " + String(dash.lPer100, 1) + " L/100km (" + srcTag + ")");
    String loadStr = dash.load.valid ? String((int)dash.load.value) + "%" : String("--");
    String thrStr = dash.throttle.valid
                        ? String((int)dash.throttle.value) + "% (" + dash.lastThrottleTag + ")"
                        : String("--");
    String battStr = dash.battery.valid ? String(dash.battery.value, 1) + " V" : String("--");
    padprintln("Load: " + loadStr + "  Thr: " + thrStr);
    padprintln("Batt: " + battStr);
    padprintln("[scroll] menu  [Esc] exit");
}

void setTankSize(ObdDashboard &dash) {
    String input = num_keyboard(String((int)dash.tankL), 4, "Tank size (L):");
    float value = input.toFloat();
    if (value <= 0) return;
    dash.tankL = value;
    saveTankSize(value);
    if (dash.haveLevel) dash.lastLiters = dash.lastPercent / obd::PERCENT_SCALE * dash.tankL;
}

void setDefaultConsumption(ObdDashboard &dash) {
    String input = num_keyboard(String(dash.defaultLPer100, 1), 4, "Cons L/100km:");
    float value = input.toFloat();
    if (value > 0) dash.defaultLPer100 = value;
}

void openTankMenu(ObdDashboard &dash) {
    String forceDefaultLabel = dash.forceDefault ? "Force default: ON" : "Force default: OFF";
    options = {
        {"Set tank size",   [&dash]() { setTankSize(dash); }                     },
        {"Set consumption", [&dash]() { setDefaultConsumption(dash); }           },
        {forceDefaultLabel, [&dash]() { dash.forceDefault = !dash.forceDefault; }},
        {"Back",            []() {}                                              },
        {"Main menu",       [&dash]() { dash.exitToMain = true; }                },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "OBD Dashboard");
}

// Scroll is latched here too because the input task clears unconsumed presses after ~75ms.
bool pollInput(ObdDashboard &dash) {
    if (check(NextPress) || check(PrevPress)) dash.menuRequested = true;
    return check(EscPress);
}

bool promptEndpoint(String &outHost, uint16_t &outPort) {
    outHost = num_keyboard(DEFAULT_OBD_HOST, 15, "OBD dongle IP:");
    if (outHost == "\x1B") return false;
    String portText = num_keyboard(String(DEFAULT_OBD_PORT), 5, "OBD dongle port:");
    if (portText == "\x1B") return false;
    long port = strtol(portText.c_str(), nullptr, 10);
    bool portValid = port > 0 && port <= MAX_TCP_PORT;
    outPort = (outHost.length() == 0 || !portValid) ? DEFAULT_OBD_PORT : (uint16_t)port;
    if (outHost.length() == 0) outHost = DEFAULT_OBD_HOST;
    return true;
}

void runDashboard(ObdDashboard &dash) {
    draw(dash);
    unsigned long lastDrawMs = millis();
    while (!dash.exitToMain && !dash.elm.aborted()) {
        if (pollInput(dash)) break;
        if (dash.menuRequested) {
            dash.menuRequested = false;
            openTankMenu(dash);
            draw(dash);
            lastDrawMs = millis();
            continue;
        }
        bool ranTask = runDueTask(dash);
        // Redraw at least once a second so the "Ns ago" counter keeps ticking.
        if (ranTask || millis() - lastDrawMs >= OBD_REDRAW_INTERVAL_MS) {
            draw(dash);
            lastDrawMs = millis();
        }
        delay(OBD_INPUT_POLL_MS);
    }
}

} // namespace

void obd_dashboard_setup() {
    if (!ensureWifiConnected("WiFi not connected")) return;

    String host;
    uint16_t port;
    if (!promptEndpoint(host, port)) return;

    ObdDashboard dash(host, port);
    dash.elm.setAbortCheck([&dash]() { return pollInput(dash); });
    displayInfo("Connecting...");
    if (!dash.elm.open()) {
        displayError("OBD connect failed: " + dash.elm.hostPort());
        return;
    }
    if (!dash.elm.aborted()) {
        probeAdapter(dash);
        buildTasks(dash);
        runDashboard(dash);
    }
    dash.elm.close();
}

#endif // LITE_VERSION
