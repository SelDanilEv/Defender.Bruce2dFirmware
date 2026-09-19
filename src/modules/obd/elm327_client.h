#if !defined(LITE_VERSION)
#ifndef ELM327_CLIENT_H
#define ELM327_CLIENT_H

#include "modules/obd/obd_pids.h"

#include <WString.h>
#include <WiFiClient.h>
#include <functional>

constexpr const char *OBD_LOG_MODULE = "obd";

struct ElmReply {
    String raw;
    obd::ReplyStatus status = obd::ReplyStatus::NoMatch;
    bool complete = false;

    bool hasData() const { return complete && status == obd::ReplyStatus::Data; }
};

// WiFi ELM327 transport: framed queries, reply/command pairing, and link recovery.
class Elm327Client {
public:
    static constexpr unsigned long STEADY_DEADLINE_MS = 2000;
    // The ELM327 defers protocol auto-search to the first data query after ATSP0.
    static constexpr unsigned long FIRST_DATA_DEADLINE_MS = 8000;
    static constexpr unsigned long RESET_DEADLINE_MS = 2000;

    Elm327Client(const String &host, uint16_t port) : host(host), port(port) {}

    void setAbortCheck(std::function<bool()> hook) { abortCheck = hook; }
    bool aborted() const { return abortRequested; }
    bool responding() const { return adapterResponding; }
    const String &hostPort() const { return hostPortLabel; }

    bool open();
    void close();
    // Recovers a silent or dropped link; false while the adapter is unreachable.
    bool ensureLink();

    ElmReply query(const String &cmd, const char *expectedTag, unsigned long deadlineMs);
    // Uses the long auto-search deadline once after (re)initialization, then the steady one.
    ElmReply queryData(const String &cmd, const char *expectedTag);

private:
    static constexpr int RESYNC_FAILURE_THRESHOLD = 3;
    static constexpr int RECONNECT_FAILURE_THRESHOLD = 6;
    static constexpr unsigned long CONNECT_TIMEOUT_MS = 3000;
    static constexpr unsigned long PROMPT_PASSIVE_WAIT_MS = 300;
    static constexpr unsigned long PROMPT_RESYNC_WAIT_MS = 3000;
    static constexpr unsigned long LONE_QUESTION_GRACE_MS = 200;
    static constexpr unsigned long WAIT_STEP_MS = 10;

    String host;
    uint16_t port;
    String hostPortLabel = host + ":" + String(port);
    WiFiClient client;
    std::function<bool()> abortCheck;

    bool abortRequested = false;
    bool adapterResponding = false;
    bool awaitingPrompt = false;
    bool pendingLongDeadline = true;
    bool softResetDone = false;
    int consecutiveFailures = 0;
    int reconnectAttempts = 0;
    unsigned long lastReconnectAttemptMs = 0;

    bool pollAbort();
    void initAdapter(const char *resetCmd);
    unsigned long reconnectBackoffMs() const;
    bool reconnect();
    void softReset();
    bool waitForPrompt(unsigned long waitMs, String &drained);
    bool resyncPrompt();
    void drainStale(const char *expectedTag);
    void recordOutcome(bool gotReply);
    ElmReply finishFrame(const String &frame, obd::ReplyStatus status);
};

#endif // ELM327_CLIENT_H
#endif // LITE_VERSION
