#include "modules/wifi/wifi_repeater_state.h"

#if defined(T_EMBED_1101)

namespace wifi_repeater {

const char* failureText(RepeaterFailure failure) {
    switch (failure) {
        case RepeaterFailure::None: return "";
        case RepeaterFailure::RadioMemory: return "low radio memory";
        case RepeaterFailure::Scan: return "scan failed";
        case RepeaterFailure::UpstreamConnection: return "upstream connection failed";
        case RepeaterFailure::UpstreamTimeout: return "upstream timeout";
        case RepeaterFailure::SoftAp: return "access point failed";
        case RepeaterFailure::SoftApDisconnect: return "access point stop failed";
        case RepeaterFailure::Napt: return "NAPT failed";
        case RepeaterFailure::NaptDisable: return "NAPT stop failed";
        case RepeaterFailure::StaDisconnect: return "station disconnect failed";
        case RepeaterFailure::WifiOff: return "WiFi off failed";
        case RepeaterFailure::Cancelled: return "cancelled";
        case RepeaterFailure::UpstreamLost: return "upstream lost";
        case RepeaterFailure::UnsupportedSecurity: return "unsupported security";
    }
    return "repeater failed";
}

void RepeaterState::beginScan() {
    stop();
    phase_ = RepeaterPhase::Scanning;
}

void RepeaterState::beginConnection() {
    stop();
    phase_ = RepeaterPhase::Connecting;
}

void RepeaterState::claimWifiModeChange() { markWifiOwned(); }

void RepeaterState::markWifiOwned() { wifiOwned_ = true; }

bool RepeaterState::markUpstreamConnected(uint8_t channel) {
    if (phase_ != RepeaterPhase::Connecting || channel == 0) return false;
    channel_ = channel;
    staConnected_ = true;
    phase_ = RepeaterPhase::StartingAccessPoint;
    return true;
}

bool RepeaterState::markAccessPointStarted() {
    if (phase_ != RepeaterPhase::StartingAccessPoint) return false;
    accessPointStarted_ = true;
    phase_ = RepeaterPhase::EnablingNapt;
    return true;
}

void RepeaterState::markNaptAttempted() { naptAttempted_ = true; }

bool RepeaterState::markNaptEnabled() {
    if (phase_ != RepeaterPhase::EnablingNapt || !naptAttempted_) return false;
    naptEnabled_ = true;
    phase_ = RepeaterPhase::Running;
    return true;
}

void RepeaterState::fail(RepeaterFailure failure) {
    phase_ = RepeaterPhase::Failed;
    failure_ = failure;
}

void RepeaterState::cancel() { fail(RepeaterFailure::Cancelled); }

void RepeaterState::loseUpstream() { fail(RepeaterFailure::UpstreamLost); }

void RepeaterState::stop() {
    phase_ = RepeaterPhase::Idle;
    failure_ = RepeaterFailure::None;
    channel_ = 0;
    wifiOwned_ = false;
    staConnected_ = false;
    accessPointStarted_ = false;
    naptAttempted_ = false;
    naptEnabled_ = false;
}

RepeaterPhase RepeaterState::phase() const { return phase_; }

RepeaterFailure RepeaterState::failure() const { return failure_; }

uint8_t RepeaterState::channel() const { return channel_; }

bool RepeaterState::wifiOwned() const { return wifiOwned_; }

bool RepeaterState::staConnected() const { return staConnected_; }

bool RepeaterState::accessPointStarted() const { return accessPointStarted_; }

bool RepeaterState::naptEnabled() const { return naptEnabled_; }

bool RepeaterState::needsNaptDisable() const { return naptAttempted_; }

bool RepeaterState::needsCleanup() const {
    return wifiOwned_ || staConnected_ || accessPointStarted_ || naptAttempted_;
}

bool RepeaterState::applyCleanupResult(CleanupAction action, bool succeeded) {
    if (!succeeded) {
        switch (action) {
            case CleanupAction::DisableNapt: fail(RepeaterFailure::NaptDisable); break;
            case CleanupAction::StopAccessPoint: fail(RepeaterFailure::SoftApDisconnect); break;
            case CleanupAction::DisconnectStation: fail(RepeaterFailure::StaDisconnect); break;
            case CleanupAction::PowerOffWifi: fail(RepeaterFailure::WifiOff); break;
        }
        return false;
    }

    switch (action) {
        case CleanupAction::DisableNapt:
            naptAttempted_ = false;
            naptEnabled_ = false;
            break;
        case CleanupAction::StopAccessPoint: accessPointStarted_ = false; break;
        case CleanupAction::DisconnectStation: staConnected_ = false; break;
        case CleanupAction::PowerOffWifi: wifiOwned_ = false; break;
    }
    return true;
}

CleanupPlan RepeaterState::cleanupPlan() const {
    CleanupPlan plan{};
    if (naptAttempted_) plan.actions[plan.count++] = CleanupAction::DisableNapt;
    if (accessPointStarted_) plan.actions[plan.count++] = CleanupAction::StopAccessPoint;
    if (wifiOwned_) plan.actions[plan.count++] = CleanupAction::DisconnectStation;
    if (wifiOwned_) plan.actions[plan.count++] = CleanupAction::PowerOffWifi;
    return plan;
}

}

#endif
