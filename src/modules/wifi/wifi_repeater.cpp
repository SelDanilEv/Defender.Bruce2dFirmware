#include "modules/wifi/wifi_repeater.h"

#if defined(T_EMBED_1101)

#include <WiFi.h>
#include <esp_netif.h>
#include <esp_netif_net_stack.h>
#include <lwip/netif.h>

#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/radio_mem.h"
#include "core/wifi/wifi_common.h"
#include "core/wifi/wifi_mac.h"
#include "core/wifi/webInterface.h"
#include "modules/ble/ble_common.h"
#include "modules/wifi/wifi_repeater_state.h"
#include <globals.h>

namespace {

wifi_repeater::RepeaterState repeaterState;
String repeaterUpstreamSsid;
uint8_t repeaterChannel = 0;
const IPAddress kRepeaterGateway(172, 0, 0, 1);

constexpr uint8_t kNaptDisableAttempts = 3;
constexpr uint32_t kNaptDisableRetryDelayMs = 20;
constexpr uint8_t kCleanupAttempts = 3;
constexpr uint32_t kCleanupRetryDelayMs = 20;
constexpr uint32_t kAccessPointSettleDelayMs = 250;
constexpr uint32_t kNaptEnableTimeoutMs = 3000;
constexpr uint32_t kNaptEnableRetryDelayMs = 100;

struct DnsStatus {
    IPAddress server;
    bool tested = false;
    bool ok = false;
};

DnsStatus repeaterDns;

struct RunningStatusLayout {
    int16_t clientsY = 0;
};

RunningStatusLayout runningLayout;

bool failAndCleanup(wifi_repeater::RepeaterFailure failure);
bool accessPointNetifUp();
void showFailure(wifi_repeater::RepeaterFailure failure);

template <typename Operation>
bool retryCleanupOperation(Operation operation) {
    for (uint8_t attempt = 0; attempt < kCleanupAttempts; attempt++) {
        if (operation()) return true;
        if (attempt + 1 < kCleanupAttempts) delay(kCleanupRetryDelayMs);
    }
    return false;
}

bool radioFullyIdle() {
    return WiFi.getMode() == WIFI_MODE_NULL && !WiFi.AP.started() && WiFi.status() != WL_CONNECTED;
}

bool runCleanupAction(wifi_repeater::CleanupAction action) {
    switch (action) {
        case wifi_repeater::CleanupAction::DisableNapt:
            // A down AP netif cannot route and is re-added with NAPT cleared.
            if (!accessPointNetifUp()) return true;
            for (uint8_t attempt = 0; attempt < kNaptDisableAttempts; attempt++) {
                if (WiFi.AP.enableNAPT(false)) return true;
                delay(kNaptDisableRetryDelayMs);
            }
            return false;
        case wifi_repeater::CleanupAction::StopAccessPoint:
            if (!WiFi.AP.started()) return true;
            return retryCleanupOperation([]() { return WiFi.softAPdisconnect(false); });
        case wifi_repeater::CleanupAction::DisconnectStation:
            if (WiFi.status() != WL_CONNECTED) return true;
            return retryCleanupOperation([]() { return WiFi.disconnect(false, true); });
        case wifi_repeater::CleanupAction::PowerOffWifi:
            return retryCleanupOperation([]() {
                if (WiFi.getMode() == WIFI_MODE_NULL) return true;
                if (!WiFi.mode(WIFI_OFF)) return false;
                return WiFi.getMode() == WIFI_MODE_NULL;
            });
    }
    return false;
}

bool clearRepeaterState() {
    const wifi_repeater::CleanupPlan cleanupPlan = repeaterState.cleanupPlan();

    for (uint8_t index = 0; index < cleanupPlan.count; index++) {
        const wifi_repeater::CleanupAction action = cleanupPlan.actions[index];
        const bool succeeded = runCleanupAction(action);
        repeaterState.applyCleanupResult(action, succeeded);
        if (succeeded) vTaskDelay(pdMS_TO_TICKS(10));
    }

    if (!repeaterState.needsCleanup()) {
        wifiConnected = false;
        wifiIP = "";
        repeaterUpstreamSsid = "";
        repeaterChannel = 0;
        repeaterState.stop();
        return true;
    }

    if (radioFullyIdle()) {
        wifiConnected = false;
        wifiIP = "";
    }
    return false;
}

void prepareRepeater() {
    cleanlyStopWebUiForWiFiFeature();
    if (FORCE_RADIO_TEARDOWN_ON_SWITCH || BLEConnected) {
        stopBLEStack();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

bool chooseUpstream(String& ssid, String& password, int& encryption) {
    repeaterState.beginScan();
    drawMainBorderWithTitle("WiFi Repeater");

    repeaterState.claimWifiModeChange();
    if (!WiFi.mode(WIFI_MODE_STA)) {
        failAndCleanup(wifi_repeater::RepeaterFailure::Scan);
        return false;
    }

    encryption = WIFI_AUTH_OPEN;
    if (!selectWifiNetwork(ssid, encryption)) {
        if (!clearRepeaterState()) showFailure(repeaterState.failure());
        return false;
    }

    if (encryption == WIFI_AUTH_WEP || encryption == WIFI_AUTH_WPA2_ENTERPRISE) {
        failAndCleanup(wifi_repeater::RepeaterFailure::UnsupportedSecurity);
        return false;
    }

    if (encryption != WIFI_AUTH_OPEN) {
        password = bruceConfig.getWifiPassword(ssid);
        if (!password.isEmpty()) return true;
        password = keyboard("", 63, "Network Password:", true);
        if (password == "\x1B") {
            if (!clearRepeaterState()) showFailure(repeaterState.failure());
            return false;
        }
    } else {
        password = "";
    }
    return true;
}

void showFailure(wifi_repeater::RepeaterFailure failure) {
    displayError(String("Repeater: ") + wifi_repeater::failureText(failure), true);
}

bool failAndCleanup(wifi_repeater::RepeaterFailure failure) {
    repeaterState.fail(failure);
    if (!clearRepeaterState()) {
        showFailure(repeaterState.failure());
        return false;
    }
    showFailure(failure);
    return true;
}

void cancelAndCleanup() {
    repeaterState.cancel();
    if (!clearRepeaterState()) showFailure(repeaterState.failure());
}

enum class ConnectAttemptResult { Connected, Cancelled, ConnectFailed, TimedOut };

ConnectAttemptResult attemptUpstreamConnect(const String& ssid, const String& password) {
    WiFi.begin(ssid, password);

    const uint32_t startedAt = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (check(EscPress) || check(SelPress)) return ConnectAttemptResult::Cancelled;
        const wl_status_t status = WiFi.status();
        if (status == WL_CONNECT_FAILED || status == WL_NO_SSID_AVAIL) {
            return ConnectAttemptResult::ConnectFailed;
        }
        if (millis() - startedAt >= wifi_repeater::kUpstreamConnectionTimeoutMs) {
            return ConnectAttemptResult::TimedOut;
        }
        delay(100);
    }
    return ConnectAttemptResult::Connected;
}

// Prompts Retry/Cancel and, on Retry, a password re-entry, matching _wifiConnect's pattern in
// wifi_common.cpp. Returns the password to retry with, or "\x1B" if the user cancelled.
String promptPasswordRetry(const String& previousPassword) {
    wakeUpScreen();
    bool retry = false;
    options = {
        {"Retry",  [&]() { retry = true; } },
        {"Cancel", [&]() { retry = false; }},
    };
    loopOptions(options);
    if (!retry) return "\x1B";
    return keyboard(previousPassword, 63, "Network Password:", true);
}

bool connectUpstreamWithRetry(const String& ssid, String& password, int encryption) {
    ConnectAttemptResult result = attemptUpstreamConnect(ssid, password);
    while (result != ConnectAttemptResult::Connected) {
        if (result == ConnectAttemptResult::Cancelled) return false;

        if (encryption == WIFI_AUTH_OPEN) {
            failAndCleanup(
                result == ConnectAttemptResult::TimedOut ? wifi_repeater::RepeaterFailure::UpstreamTimeout
                                                          : wifi_repeater::RepeaterFailure::UpstreamConnection
            );
            return false;
        }

        const String nextPassword = promptPasswordRetry(password);
        if (nextPassword == "\x1B") return false;
        password = nextPassword;
        result = attemptUpstreamConnect(ssid, password);
    }
    return true;
}

bool accessPointNetifUp() {
    esp_netif_t* apNetif = WiFi.AP.netif();
    return WiFi.AP.started() && apNetif != nullptr && esp_netif_is_netif_up(apNetif);
}

bool naptActiveOnAccessPoint() {
    if (!accessPointNetifUp()) return false;
    const struct netif* lwipNetif = static_cast<struct netif*>(esp_netif_get_netif_impl(WiFi.AP.netif()));
    return lwipNetif != nullptr && lwipNetif->napt != 0;
}

void logNaptFailure(const char* reason, esp_err_t error, const IPAddress& gateway) {
    const bool started = WiFi.AP.started();
    const bool netifUp = accessPointNetifUp();
    const String apIp = WiFi.softAPIP().toString();
    log_e(
        "Repeater NAPT failed: %s, err=0x%x %s, apStarted=%d, netifUp=%d, apIp=%s, expected=%s",
        reason,
        error,
        esp_err_to_name(error),
        started,
        netifUp,
        apIp.c_str(),
        gateway.toString().c_str()
    );
    Serial.printf(
        "[Repeater] NAPT failed: %s, err=0x%x %s, apStarted=%d, netifUp=%d, apIp=%s, expected=%s\n",
        reason,
        error,
        esp_err_to_name(error),
        started,
        netifUp,
        apIp.c_str(),
        gateway.toString().c_str()
    );
}

// softAP() restarts a running AP asynchronously: the netif goes down and netif_add clears NAPT.
bool enableNaptWhenAccessPointReady(const IPAddress& gateway) {
    delay(kAccessPointSettleDelayMs);

    const uint32_t startedAt = millis();
    const char* reason = "AP netif not up";
    esp_err_t lastError = ESP_ERR_INVALID_STATE;

    while (true) {
        if (accessPointNetifUp() && WiFi.softAPIP() == gateway) {
            lastError = esp_netif_napt_enable(WiFi.AP.netif());
            if (lastError == ESP_ERR_NOT_SUPPORTED) {
                reason = "NAPT not supported by lwip build";
                break;
            }
            if (lastError == ESP_OK) {
                delay(kNaptEnableRetryDelayMs);
                if (naptActiveOnAccessPoint()) return true;
                reason = "NAPT cleared by AP restart";
                lastError = ESP_ERR_INVALID_STATE;
            } else {
                reason = "esp_netif_napt_enable failed";
            }
        } else {
            reason = "AP netif not up";
            lastError = ESP_ERR_INVALID_STATE;
        }

        if (millis() - startedAt >= kNaptEnableTimeoutMs) break;
        delay(kNaptEnableRetryDelayMs);
    }

    logNaptFailure(reason, lastError, gateway);
    return false;
}

bool startRepeater(const String& ssid, const String& initialPassword, int encryption) {
    repeaterUpstreamSsid = ssid;
    repeaterDns = DnsStatus{};
    repeaterState.beginConnection();
    drawMainBorderWithTitle("WiFi Repeater");
    displayTextLine("Connecting upstream...");

    repeaterState.claimWifiModeChange();
    if (!WiFi.mode(WIFI_MODE_APSTA)) {
        failAndCleanup(wifi_repeater::RepeaterFailure::UpstreamConnection);
        return false;
    }
    applyConfiguredMAC();

    String password = initialPassword;
    if (!connectUpstreamWithRetry(ssid, password, encryption)) {
        cancelAndCleanup();
        return false;
    }

    repeaterChannel = static_cast<uint8_t>(WiFi.channel());
    if (!repeaterState.markUpstreamConnected(repeaterChannel)) {
        failAndCleanup(wifi_repeater::RepeaterFailure::UpstreamConnection);
        return false;
    }
    if (bruceConfig.getWifiPassword(ssid) != password) bruceConfig.addWifiCredential(ssid, password);

    displayTextLine("Starting access point...");
    const IPAddress& gateway = kRepeaterGateway;
    const IPAddress upstreamDns = WiFi.dnsIP(0);
    const IPAddress apDns = (upstreamDns == IPAddress(0, 0, 0, 0)) ? IPAddress(1, 1, 1, 1) : upstreamDns;
    repeaterDns.server = apDns;

    if (!WiFi.softAPConfig(gateway, gateway, IPAddress(255, 255, 255, 0), IPAddress((uint32_t)0), apDns) ||
        !WiFi.softAP(
            bruceConfig.repeaterAp.ssid,
            bruceConfig.repeaterAp.pwd,
            repeaterChannel,
            0,
            4,
            false
        )) {
        failAndCleanup(wifi_repeater::RepeaterFailure::SoftAp);
        return false;
    }
    if (!repeaterState.markAccessPointStarted()) {
        failAndCleanup(wifi_repeater::RepeaterFailure::SoftAp);
        return false;
    }

    repeaterState.markNaptAttempted();
    if (!enableNaptWhenAccessPointReady(gateway) || !repeaterState.markNaptEnabled()) {
        failAndCleanup(wifi_repeater::RepeaterFailure::Napt);
        return false;
    }

    IPAddress dnsTestResult;
    repeaterDns.tested = true;
    repeaterDns.ok = (WiFi.hostByName("dns.google", dnsTestResult) == 1);

    wifiConnected = true;
    wifiIP = WiFi.softAPIP().toString();
    return true;
}

String dnsStatusLine() {
    const String status = !repeaterDns.tested ? "..." : (repeaterDns.ok ? "OK" : "FAIL");
    return "DNS: " + repeaterDns.server.toString() + " " + status;
}

void drawRunningStatusStatic() {
    drawMainBorderWithTitle("WiFi Repeater");
    padprintln("Upstream: " + repeaterUpstreamSsid);
    padprintln("AP SSID: " + bruceConfig.repeaterAp.ssid);
    padprintln("AP Password: " + bruceConfig.repeaterAp.pwd);
    padprintln("Channel: " + String(repeaterChannel));
    padprintln("STA IP: " + WiFi.localIP().toString());
    padprintln("AP IP: " + WiFi.softAPIP().toString());
    runningLayout.clientsY = tft.getCursorY();
    padprintln("Clients: " + String(WiFi.softAPgetStationNum()));
    padprintln(dnsStatusLine());
    padprintln("Scroll: menu  Back: exit");
}

void redrawValueLine(int16_t y, const String& text) {
    const int lineHeight = max(1, FP * LH);
    tft.fillRect(BORDER_PAD_X, y, tftWidth - (BORDER_PAD_X * 2), lineHeight, bruceConfig.bgColor);
    tft.setCursor(BORDER_PAD_X, y);
    tft.print(text);
}

void updateRunningStatusValues() {
    redrawValueLine(runningLayout.clientsY, "Clients: " + String(WiFi.softAPgetStationNum()));
}

// Polls for the upstream link to recover on its own (ESP32 STA auto-reconnect) without
// re-issuing WiFi.begin. Returns false if the grace period elapses or the user cancels.
bool waitForUpstreamRecovery() {
    displayTextLine("Upstream lost, reconnecting...");
    const uint32_t startedAt = millis();
    while (millis() - startedAt < wifi_repeater::kUpstreamLostGraceMs) {
        if (check(EscPress)) return false;
        if (WiFi.status() == WL_CONNECTED) return true;
        delay(100);
    }
    return WiFi.status() == WL_CONNECTED;
}

// Restarts the softAP with new credentials on the same channel and IP config, then
// re-enables NAPT since softAP() clears it. Calls failAndCleanup and returns false on failure.
bool applyAccessPointCredentials(const String& ssid, const String& pwd) {
    bruceConfig.repeaterAp.ssid = ssid;
    bruceConfig.repeaterAp.pwd = pwd;
    bruceConfig.saveFile();

    if (!WiFi.softAPConfig(
            kRepeaterGateway,
            kRepeaterGateway,
            IPAddress(255, 255, 255, 0),
            IPAddress((uint32_t)0),
            repeaterDns.server
        ) ||
        !WiFi.softAP(bruceConfig.repeaterAp.ssid, bruceConfig.repeaterAp.pwd, repeaterChannel, 0, 4, false)) {
        failAndCleanup(wifi_repeater::RepeaterFailure::SoftAp);
        return false;
    }
    if (!enableNaptWhenAccessPointReady(kRepeaterGateway)) {
        failAndCleanup(wifi_repeater::RepeaterFailure::Napt);
        return false;
    }
    return true;
}

// Returns false only if the apply failed and runRepeater must exit (failAndCleanup already ran).
bool promptApName() {
    const String value = keyboard(bruceConfig.repeaterAp.ssid, 32, "AP Name:");
    if (value == "\x1B" || value == bruceConfig.repeaterAp.ssid) return true;
    if (value.isEmpty() || value.length() > 32) {
        displayError("Invalid AP name", true);
        return true;
    }
    return applyAccessPointCredentials(value, bruceConfig.repeaterAp.pwd);
}

// Returns false only if the apply failed and runRepeater must exit (failAndCleanup already ran).
bool promptApPassword() {
    const String value = keyboard(bruceConfig.repeaterAp.pwd, 63, "AP Password:", true);
    if (value == "\x1B" || value == bruceConfig.repeaterAp.pwd) return true;
    if (value.length() < 8 || value.length() > 63) {
        displayError("Invalid AP password", true);
        return true;
    }
    return applyAccessPointCredentials(bruceConfig.repeaterAp.ssid, value);
}

// Result of a status screen menu visit. Only Stop actually tears the repeater down;
// Failed means applying a credential change already ran failAndCleanup.
enum class ApMenuResult { Continue, Stop, Failed };

ApMenuResult showRepeaterApMenu() {
    ApMenuResult result = ApMenuResult::Continue;
    options = {
        {"Change name",     [&]() { if (!promptApName()) result = ApMenuResult::Failed; }    },
        {"Change password", [&]() { if (!promptApPassword()) result = ApMenuResult::Failed; }},
        {"Stop repeater",   [&]() { result = ApMenuResult::Stop; }                            },
        {"Back",             []() {}                                                          },
    };
    loopOptions(options);
    return result;
}

// Outcome of a status screen visit. Physical Back only leaves the status screen: the
// repeater (softAP, STA, NAPT) keeps running in the background until "Stop repeater"
// is chosen from the scroll menu or the connection itself fails.
enum class RunOutcome { LeftRunning, Stopped, Failed };

RunOutcome runRepeater() {
    drawRunningStatusStatic();

    while (true) {
        const unsigned long tickStartedAt = millis();
        while (millis() - tickStartedAt < 500) {
            if (check(EscPress)) return RunOutcome::LeftRunning;
            if (check(PrevPress) || check(NextPress)) {
                const ApMenuResult menuResult = showRepeaterApMenu();
                if (menuResult == ApMenuResult::Failed) return RunOutcome::Failed;
                if (menuResult == ApMenuResult::Stop) return RunOutcome::Stopped;
                drawRunningStatusStatic();
            }
            delay(20);
        }

        if (WiFi.status() != WL_CONNECTED) {
            // NAPT and the softAP's own config are independent of the STA link: they were
            // set up once against the AP interface and are untouched by the STA reconnecting,
            // so no re-verification is needed here.
            if (!waitForUpstreamRecovery()) {
                failAndCleanup(wifi_repeater::RepeaterFailure::UpstreamLost);
                return RunOutcome::Failed;
            }
            drawRunningStatusStatic();
            continue;
        }

        updateRunningStatusValues();
    }
}

// failAndCleanup (Failed) already tore the repeater down and reported the error; only a
// user-requested Stop still needs the normal, non-failure cleanup path run here.
void finishRunRepeater(RunOutcome outcome) {
    if (outcome != RunOutcome::Stopped) return;
    if (repeaterState.needsCleanup() && !clearRepeaterState()) showFailure(repeaterState.failure());
}

}

void wifiRepeater() {
    if (isWifiTransitioning()) {
        displayTextLine("WiFi busy, please wait...");
        vTaskDelay(500 / portTICK_PERIOD_MS);
        return;
    }

    // The repeater was left running in the background (physical Back on the status
    // screen). Reopening this menu item goes straight back to the status screen instead
    // of tearing down and re-selecting an upstream network. WiFi.AP.started() guards
    // against a stale Running phase left behind by another feature tearing the radio
    // down directly (e.g. wifiDisconnect() called elsewhere) without going through us.
    if (repeaterState.phase() == wifi_repeater::RepeaterPhase::Running && WiFi.AP.started()) {
        finishRunRepeater(runRepeater());
        return;
    }

    if (repeaterState.needsCleanup() && !clearRepeaterState()) {
        showFailure(repeaterState.failure());
        return;
    }

    if (WiFi.getMode() != WIFI_MODE_NULL || wifiConnected || WiFi.AP.started()) {
        cleanlyStopWebUiForWiFiFeature();
        wifiDisconnect();
    }
    if (WiFi.getMode() != WIFI_MODE_NULL || wifiConnected || WiFi.AP.started()) {
        displayError("Turn off WiFi first", true);
        return;
    }

    if (!radioHasMemForWifi()) {
        displayError("Repeater: low radio memory", true);
        return;
    }

    bruceConfig.ensureRepeaterApCredentials();
    prepareRepeater();

    String upstreamSsid;
    String upstreamPassword;
    int upstreamEncryption = WIFI_AUTH_OPEN;
    if (!chooseUpstream(upstreamSsid, upstreamPassword, upstreamEncryption)) return;
    if (!startRepeater(upstreamSsid, upstreamPassword, upstreamEncryption)) return;
    finishRunRepeater(runRepeater());
}

#endif
