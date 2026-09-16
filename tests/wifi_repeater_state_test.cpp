#include "modules/wifi/wifi_repeater_state.h"

#include <cassert>
#include <cstring>

void testModeChangeClaimsWifiBeforeResult() {
    using namespace wifi_repeater;

    RepeaterState state;
    state.beginConnection();
    state.claimWifiModeChange();

    const CleanupPlan cleanupPlan = state.cleanupPlan();
    assert(cleanupPlan.count == 2);
    assert(cleanupPlan.actions[0] == CleanupAction::DisconnectStation);
    assert(cleanupPlan.actions[1] == CleanupAction::PowerOffWifi);
}

void testCleanupFailuresKeepPendingState() {
    using namespace wifi_repeater;

    struct CleanupFailureCase {
        CleanupAction action;
        RepeaterFailure failure;
    };
    const CleanupFailureCase cases[] = {
        {CleanupAction::StopAccessPoint, RepeaterFailure::SoftApDisconnect},
        {CleanupAction::DisconnectStation, RepeaterFailure::StaDisconnect},
        {CleanupAction::PowerOffWifi, RepeaterFailure::WifiOff},
    };

    for (const CleanupFailureCase& testCase : cases) {
        RepeaterState state;
        state.beginConnection();
        state.claimWifiModeChange();
        assert(state.markUpstreamConnected(11));
        assert(state.markAccessPointStarted());
        state.markNaptAttempted();
        assert(state.markNaptEnabled());

        assert(!state.applyCleanupResult(testCase.action, false));
        assert(state.phase() == RepeaterPhase::Failed);
        assert(state.failure() == testCase.failure);
        assert(state.needsCleanup());

        const CleanupPlan cleanupPlan = state.cleanupPlan();
        bool actionStillPending = false;
        for (uint8_t index = 0; index < cleanupPlan.count; index++) {
            actionStillPending = actionStillPending || cleanupPlan.actions[index] == testCase.action;
        }
        assert(actionStillPending);
    }
}

void testPartialCleanupRetriesOnlyPendingActions() {
    using namespace wifi_repeater;

    RepeaterState state;
    state.beginConnection();
    state.claimWifiModeChange();
    assert(state.markUpstreamConnected(6));
    assert(state.markAccessPointStarted());
    state.markNaptAttempted();
    assert(state.markNaptEnabled());

    const CleanupPlan firstPlan = state.cleanupPlan();
    assert(firstPlan.count == 4);

    assert(state.applyCleanupResult(CleanupAction::DisableNapt, true));
    assert(!state.applyCleanupResult(CleanupAction::StopAccessPoint, false));
    assert(state.applyCleanupResult(CleanupAction::DisconnectStation, true));
    assert(state.applyCleanupResult(CleanupAction::PowerOffWifi, true));

    assert(state.needsCleanup());

    const CleanupPlan secondPlan = state.cleanupPlan();
    assert(secondPlan.count == 1);
    assert(secondPlan.actions[0] == CleanupAction::StopAccessPoint);

    assert(state.applyCleanupResult(CleanupAction::StopAccessPoint, true));
    assert(!state.needsCleanup());
    assert(state.cleanupPlan().count == 0);
}

int main() {
    using namespace wifi_repeater;

    assert(kUpstreamConnectionTimeoutMs == 15000);
    assert(kUpstreamLostGraceMs == 10000);
    assert(std::strcmp(failureText(RepeaterFailure::UnsupportedSecurity), "unsupported security") == 0);

    RepeaterState state;
    state.beginScan();
    assert(state.phase() == RepeaterPhase::Scanning);
    state.markWifiOwned();
    assert(state.wifiOwned());
    state.beginConnection();
    assert(state.phase() == RepeaterPhase::Connecting);
    assert(state.failure() == RepeaterFailure::None);
    assert(state.markUpstreamConnected(11));
    assert(state.phase() == RepeaterPhase::StartingAccessPoint);
    assert(state.channel() == 11);
    assert(state.markAccessPointStarted());
    assert(state.phase() == RepeaterPhase::EnablingNapt);
    state.markNaptAttempted();
    assert(state.markNaptEnabled());
    assert(state.phase() == RepeaterPhase::Running);
    assert(state.staConnected());
    assert(state.accessPointStarted());
    assert(state.naptEnabled());

    state.fail(RepeaterFailure::Napt);
    assert(state.phase() == RepeaterPhase::Failed);
    assert(state.failure() == RepeaterFailure::Napt);
    assert(state.needsNaptDisable());
    assert(state.needsCleanup());

    state.stop();
    assert(state.phase() == RepeaterPhase::Idle);
    assert(state.failure() == RepeaterFailure::None);
    assert(!state.staConnected());
    assert(!state.accessPointStarted());
    assert(!state.naptEnabled());
    assert(!state.needsNaptDisable());
    assert(!state.needsCleanup());

    assert(std::strcmp(failureText(RepeaterFailure::RadioMemory), "low radio memory") == 0);
    assert(std::strcmp(failureText(RepeaterFailure::UpstreamTimeout), "upstream timeout") == 0);
    assert(std::strcmp(failureText(RepeaterFailure::SoftAp), "access point failed") == 0);
    assert(std::strcmp(failureText(RepeaterFailure::Napt), "NAPT failed") == 0);
    assert(std::strcmp(failureText(RepeaterFailure::NaptDisable), "NAPT stop failed") == 0);

    state.beginConnection();
    state.markWifiOwned();
    assert(state.markUpstreamConnected(11));
    assert(state.markAccessPointStarted());
    state.markNaptAttempted();
    assert(state.markNaptEnabled());
    state.beginScan();
    assert(state.phase() == RepeaterPhase::Scanning);
    assert(!state.wifiOwned());
    assert(!state.staConnected());
    assert(!state.accessPointStarted());
    assert(!state.needsNaptDisable());
    assert(!state.needsCleanup());
    state.markWifiOwned();
    state.beginConnection();
    assert(state.phase() == RepeaterPhase::Connecting);
    assert(!state.wifiOwned());
    assert(!state.needsCleanup());

    state.markWifiOwned();
    assert(state.markUpstreamConnected(6));
    assert(state.markAccessPointStarted());
    state.markNaptAttempted();
    assert(state.markNaptEnabled());
    const CleanupPlan cleanupPlan = state.cleanupPlan();
    assert(cleanupPlan.count == 4);
    assert(cleanupPlan.actions[0] == CleanupAction::DisableNapt);
    assert(cleanupPlan.actions[1] == CleanupAction::StopAccessPoint);
    assert(cleanupPlan.actions[2] == CleanupAction::DisconnectStation);
    assert(cleanupPlan.actions[3] == CleanupAction::PowerOffWifi);
    state.cancel();
    assert(state.phase() == RepeaterPhase::Failed);
    assert(state.failure() == RepeaterFailure::Cancelled);
    assert(state.needsCleanup());
    state.stop();
    state.beginConnection();
    state.markWifiOwned();
    assert(state.markUpstreamConnected(1));
    state.loseUpstream();
    assert(state.phase() == RepeaterPhase::Failed);
    assert(state.failure() == RepeaterFailure::UpstreamLost);
    assert(state.needsCleanup());

    testModeChangeClaimsWifiBeforeResult();
    testCleanupFailuresKeepPendingState();
    testPartialCleanupRetriesOnlyPendingActions();

    return 0;
}
