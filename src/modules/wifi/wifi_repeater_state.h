#ifndef WIFI_REPEATER_STATE_H
#define WIFI_REPEATER_STATE_H

#if defined(T_EMBED_1101)

#include <cstdint>

namespace wifi_repeater {

constexpr uint32_t kUpstreamConnectionTimeoutMs = 15000;
constexpr uint32_t kUpstreamLostGraceMs = 10000;

enum class RepeaterPhase {
    Idle,
    Scanning,
    Connecting,
    StartingAccessPoint,
    EnablingNapt,
    Running,
    Failed,
};

enum class RepeaterFailure {
    None,
    RadioMemory,
    Scan,
    UpstreamConnection,
    UpstreamTimeout,
    SoftAp,
    SoftApDisconnect,
    Napt,
    NaptDisable,
    StaDisconnect,
    WifiOff,
    Cancelled,
    UpstreamLost,
    UnsupportedSecurity,
};

enum class CleanupAction {
    DisableNapt,
    StopAccessPoint,
    DisconnectStation,
    PowerOffWifi,
};

constexpr uint8_t kMaxCleanupActions = 4;

struct CleanupPlan {
    CleanupAction actions[kMaxCleanupActions];
    uint8_t count;
};

const char* failureText(RepeaterFailure failure);

class RepeaterState {
public:
    void beginScan();
    void beginConnection();
    void claimWifiModeChange();
    void markWifiOwned();
    bool markUpstreamConnected(uint8_t channel);
    bool markAccessPointStarted();
    void markNaptAttempted();
    bool markNaptEnabled();
    void fail(RepeaterFailure failure);
    void cancel();
    void loseUpstream();
    void stop();

    RepeaterPhase phase() const;
    RepeaterFailure failure() const;
    uint8_t channel() const;
    bool wifiOwned() const;
    bool staConnected() const;
    bool accessPointStarted() const;
    bool naptEnabled() const;
    bool needsNaptDisable() const;
    bool needsCleanup() const;
    bool applyCleanupResult(CleanupAction action, bool succeeded);
    CleanupPlan cleanupPlan() const;

private:
    RepeaterPhase phase_ = RepeaterPhase::Idle;
    RepeaterFailure failure_ = RepeaterFailure::None;
    uint8_t channel_ = 0;
    bool wifiOwned_ = false;
    bool staConnected_ = false;
    bool accessPointStarted_ = false;
    bool naptAttempted_ = false;
    bool naptEnabled_ = false;
};

}

#endif

#endif
