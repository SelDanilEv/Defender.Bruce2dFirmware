#if !defined(LITE_VERSION)
#include "modules/obd/elm327_client.h"

#include "core/debug_log.h"

#include <Arduino.h>

namespace {

const unsigned long RECONNECT_BACKOFF_MS[] = {1000, 2000, 5000};
const int RECONNECT_BACKOFF_STEPS = sizeof(RECONNECT_BACKOFF_MS) / sizeof(RECONNECT_BACKOFF_MS[0]);
const char *const INIT_SETTINGS[] = {"ATE0", "ATL0", "ATH0", "ATS0", "ATSP0"};

void appendCapped(String &buffer, char ch) {
    if (buffer.length() < obd::MAX_REPLY_LEN) buffer += ch;
}

void logLine(const char *tag, const String &text) { DebugLog::write(OBD_LOG_MODULE, tag, text); }

} // namespace

bool Elm327Client::open() {
    client.setTimeout(1);
    if (!client.connect(host.c_str(), port, CONNECT_TIMEOUT_MS)) {
        logLine("INFO", "connect failed: " + hostPortLabel);
        return false;
    }
    initAdapter("ATZ");
    return true;
}

void Elm327Client::close() { client.stop(); }

bool Elm327Client::pollAbort() {
    if (!abortRequested && abortCheck && abortCheck()) abortRequested = true;
    return abortRequested;
}

void Elm327Client::initAdapter(const char *resetCmd) {
    awaitingPrompt = false;
    if (!query(resetCmd, "", RESET_DEADLINE_MS).complete) return;
    for (const char *setting : INIT_SETTINGS) {
        if (!query(setting, "", STEADY_DEADLINE_MS).complete) return;
    }
    pendingLongDeadline = true;
}

unsigned long Elm327Client::reconnectBackoffMs() const {
    int step = reconnectAttempts - 1;
    if (step >= RECONNECT_BACKOFF_STEPS) step = RECONNECT_BACKOFF_STEPS - 1;
    return RECONNECT_BACKOFF_MS[step];
}

bool Elm327Client::ensureLink() {
    if (abortRequested) return false;
    if (!client.connected() || consecutiveFailures >= RECONNECT_FAILURE_THRESHOLD) return reconnect();
    if (consecutiveFailures >= RESYNC_FAILURE_THRESHOLD && !softResetDone) softReset();
    return !abortRequested;
}

bool Elm327Client::reconnect() {
    unsigned long now = millis();
    if (reconnectAttempts > 0 && now - lastReconnectAttemptMs < reconnectBackoffMs()) return false;
    lastReconnectAttemptMs = now;
    reconnectAttempts++;
    adapterResponding = false;
    logLine("INFO", "reconnect attempt " + String(reconnectAttempts) + " " + hostPortLabel);
    client.stop();
    if (!client.connect(host.c_str(), port, CONNECT_TIMEOUT_MS)) {
        logLine("INFO", "reconnect failed " + hostPortLabel);
        return false;
    }
    consecutiveFailures = 0;
    softResetDone = false;
    initAdapter("ATZ");
    return !abortRequested;
}

void Elm327Client::softReset() {
    softResetDone = true;
    logLine("INFO", "resync after " + String(consecutiveFailures) + " failed replies");
    awaitingPrompt = true;
    if (!resyncPrompt()) return;
    initAdapter("ATWS");
}

bool Elm327Client::waitForPrompt(unsigned long waitMs, String &drained) {
    unsigned long start = millis();
    while (millis() - start < waitMs) {
        while (client.available()) {
            int ch = client.read();
            if (ch < 0) break;
            appendCapped(drained, (char)ch);
            if (ch == '>') return true;
        }
        if (pollAbort()) return false;
        delay(WAIT_STEP_MS);
    }
    return false;
}

bool Elm327Client::resyncPrompt() {
    String drained;
    bool promptSeen = waitForPrompt(PROMPT_PASSIVE_WAIT_MS, drained);
    if (!promptSeen && !abortRequested) {
        // A bare CR makes an idle ELM327 print a fresh '>' prompt.
        logLine("INFO", "resync prompt");
        client.print("\r");
        promptSeen = waitForPrompt(PROMPT_RESYNC_WAIT_MS, drained);
    }
    if (drained.length() > 0) logLine("RX", "stale " + drained);
    if (promptSeen) awaitingPrompt = false;
    return promptSeen;
}

void Elm327Client::drainStale(const char *expectedTag) {
    String stale;
    while (client.available()) {
        int ch = client.read();
        if (ch < 0) break;
        appendCapped(stale, (char)ch);
    }
    if (stale.length() == 0) return;
    logLine("RX", "stale " + stale);
    if (expectedTag[0] != '\0' && obd::hasTagLine(stale.c_str(), stale.length(), expectedTag)) {
        logLine("INFO", String("stale had ") + expectedTag + ", discarded");
    }
}

void Elm327Client::recordOutcome(bool gotReply) {
    adapterResponding = gotReply;
    if (!gotReply) {
        consecutiveFailures++;
        return;
    }
    consecutiveFailures = 0;
    softResetDone = false;
    reconnectAttempts = 0;
}

ElmReply Elm327Client::finishFrame(const String &frame, obd::ReplyStatus status) {
    logLine("RX", frame);
    recordOutcome(true);
    ElmReply reply;
    reply.raw = frame;
    reply.status = status;
    reply.complete = true;
    return reply;
}

ElmReply Elm327Client::queryData(const String &cmd, const char *expectedTag) {
    unsigned long deadlineMs = pendingLongDeadline ? FIRST_DATA_DEADLINE_MS : STEADY_DEADLINE_MS;
    pendingLongDeadline = false;
    return query(cmd, expectedTag, deadlineMs);
}

ElmReply Elm327Client::query(const String &cmd, const char *expectedTag, unsigned long deadlineMs) {
    ElmReply timedOut;
    if (pollAbort()) return timedOut;
    if (!client.connected()) {
        recordOutcome(false);
        return timedOut;
    }
    // A late reply to a timed-out command must reach its '>' before the next command is sent.
    if (awaitingPrompt && !resyncPrompt()) {
        if (!abortRequested) {
            logLine("INFO", "prompt lost, skipped " + cmd);
            recordOutcome(false);
        }
        return timedOut;
    }
    drainStale(expectedTag);

    logLine("TX", cmd);
    client.print(cmd + "\r");

    String frame;
    String loneQuestionFrame;
    unsigned long loneQuestionAtMs = 0;
    unsigned long start = millis();
    while (millis() - start < deadlineMs) {
        while (client.available() && millis() - start < deadlineMs) {
            int ch = client.read();
            if (ch < 0) break;
            appendCapped(frame, (char)ch);
            if (ch != '>') continue;
            // Some ELM327 clones send a spurious lone "?" before the real reply.
            if (obd::isLoneQuestionMark(frame.c_str(), frame.length())) {
                logLine("RX", "skip " + frame);
                loneQuestionFrame = frame;
                loneQuestionAtMs = millis();
                frame = "";
                continue;
            }
            obd::ReplyStatus status = obd::classifyReply(frame.c_str(), frame.length(), expectedTag);
            if (status != obd::ReplyStatus::NoMatch) return finishFrame(frame, status);
            logLine("RX", "skip " + frame);
            frame = "";
        }
        if (frame.length() > 0) loneQuestionFrame = "";
        bool loneQuestionSettled =
            loneQuestionFrame.length() > 0 && millis() - loneQuestionAtMs >= LONE_QUESTION_GRACE_MS;
        if (loneQuestionSettled) return finishFrame(loneQuestionFrame, obd::ReplyStatus::Unknown);
        if (pollAbort()) return timedOut;
        delay(WAIT_STEP_MS);
    }
    if (loneQuestionFrame.length() > 0) return finishFrame(loneQuestionFrame, obd::ReplyStatus::Unknown);

    logLine("RX", frame);
    awaitingPrompt = true;
    recordOutcome(false);
    timedOut.raw = frame;
    return timedOut;
}

#endif // LITE_VERSION
