#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

// Shared SD-only debug logger, active only in debug builds (BRUCE_DEBUG_LOG defined).
// Each module logs to its own file under /BruceLogs/<module>.log, tab-separated
// "<millis>\t<TAG>\t<text>" lines, rotated once per session to <module>_prev.log,
// capped at ~512KB per file. No-op when SD is not mounted or when BRUCE_DEBUG_LOG is undefined,
// so call sites never need their own #if guards.

#include <WString.h>

namespace DebugLog {

#if defined(BRUCE_DEBUG_LOG)

void write(const String &module, const String &tag, const String &text);
void flush(const String &module);
bool active();

#else

inline void write(const String &module, const String &tag, const String &text) {}
inline void flush(const String &module) {}
inline bool active() { return false; }

#endif // BRUCE_DEBUG_LOG

} // namespace DebugLog

#endif // DEBUG_LOG_H
