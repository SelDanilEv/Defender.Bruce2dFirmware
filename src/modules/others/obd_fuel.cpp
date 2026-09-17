#if !defined(LITE_VERSION)
#include "modules/others/obd_fuel.h"

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
static const unsigned long OBD_POLL_INTERVAL_MS = 100;

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

} // namespace

void obd_fuel_setup() {
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

    sendAndDrain(client, "ATZ");
    sendAndDrain(client, "ATE0");
    sendAndDrain(client, "ATSP0");

    float tankL = 50.0f;
    float lPer100 = DEFAULT_CONSUMPTION_L_PER_100;
    float defaultLPer100 = DEFAULT_CONSUMPTION_L_PER_100;
    bool forceDefault = false;
    bool exitToMain = false;
    unsigned long lastQueryMs = 0;

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
        loopOptions(options, MENU_TYPE_SUBMENU, "OBD Fuel");
    };

    while (!exitToMain && !check(EscPress)) {
        if (lastQueryMs != 0 && millis() - lastQueryMs < OBD_QUERY_DEADLINE_MS) {
            if (check(NextPress) || check(PrevPress)) {
                openTankMenu();
                continue;
            }
            delay(OBD_POLL_INTERVAL_MS);
            continue;
        }
        lastQueryMs = millis();

        String reply = stripFrameChars(sendAndDrain(client, "012F"));

        bool supported = !isPidUnsupported(reply);

        int pidIndex = reply.indexOf("412F");
        if (pidIndex == -1) supported = false;

        float percent = 0.0f;
        float liters = 0.0f;

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
        const char *srcTag = source == SRC_FR ? "FR" : source == SRC_MAF ? "MAF" : "def";
        if (forceDefault) srcTag = "def";

        float rangeKm = 0.0f;
        if (supported) {
            String byteHex = reply.substring(pidIndex + 4, pidIndex + 6);
            long a = strtol(byteHex.c_str(), nullptr, 16);
            percent = a * 100.0f / 255.0f;
            liters = percent / 100.0f * tankL;
            rangeKm = liters / (lPer100 / 100.0f);
        }

        drawMainBorder();
        printSubtitle("OBD Fuel");
        if (supported) {
            padprintln("Level: " + String((int)percent) + "%");
            padprintln("Fuel: " + String(liters, 1) + " L");
            padprintln("Range: " + String((int)rangeKm) + " km");
        } else {
            padprintln("PID 012F not supported");
        }
        padprintln("Cons: " + String(lPer100, 1) + " L/100km (" + srcTag + ")");
        padprintln("[scroll] menu  [Esc] exit");

        if (check(NextPress) || check(PrevPress)) {
            openTankMenu();
            continue;
        }
    }

    client.stop();
}

#endif // LITE_VERSION
