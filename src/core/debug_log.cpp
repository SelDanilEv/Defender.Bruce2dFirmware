#include "core/debug_log.h"

#if defined(BRUCE_DEBUG_LOG)

#include <SD.h>
#include <globals.h>
#include <vector>

namespace DebugLog {

namespace {

const char *LOG_DIR = "/BruceLogs";
const size_t LOG_MAX_BYTES = 524288;

struct ModuleState {
    String module;
    File file;
    size_t bytesWritten = 0;
    bool full = false;
    bool open = false;
};

std::vector<ModuleState> states;

String escape(const String &s) {
    String out;
    out.reserve(s.length());
    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == '\r') out += "\\r";
        else if (c == '\n') out += "\\n";
        else out += c;
    }
    return out;
}

ModuleState &stateFor(const String &module) {
    for (auto &s : states) {
        if (s.module == module) return s;
    }
    states.push_back(ModuleState{module});
    return states.back();
}

// Rotates and opens the module's log file once per session on first use.
void openIfNeeded(ModuleState &state) {
    if (state.open) return;
    state.open = true;

    if (!SD.exists(LOG_DIR)) SD.mkdir(LOG_DIR);

    String path = String(LOG_DIR) + "/" + state.module + ".log";
    String prevPath = String(LOG_DIR) + "/" + state.module + "_prev.log";
    if (SD.exists(prevPath)) SD.remove(prevPath);
    if (SD.exists(path)) SD.rename(path, prevPath);

    state.file = SD.open(path, FILE_WRITE);
    if (!state.file) state.full = true;
}

} // namespace

void write(const String &module, const String &tag, const String &text) {
    if (!sdcardMounted) return;

    ModuleState &state = stateFor(module);
    openIfNeeded(state);
    if (state.full) return;

    String line = String(millis()) + "\t" + tag + "\t" + escape(text) + "\n";
    if (state.bytesWritten + line.length() > LOG_MAX_BYTES) {
        state.file.print(String(millis()) + "\t" + tag + "\tlog full\n");
        state.file.flush();
        state.full = true;
        return;
    }
    state.file.print(line);
    state.bytesWritten += line.length();
}

void flush(const String &module) {
    if (!sdcardMounted) return;
    ModuleState &state = stateFor(module);
    if (state.open && !state.full) state.file.flush();
}

bool active() { return sdcardMounted; }

} // namespace DebugLog

#endif // BRUCE_DEBUG_LOG
