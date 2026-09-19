#include "modules/obd/obd_pids.h"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

namespace obd {

namespace {

std::vector<std::string> strippedLines(const char *reply, size_t len) {
    std::vector<std::string> lines;
    std::string current;
    for (size_t i = 0; i < len; i++) {
        char ch = reply[i];
        if (ch == '\r' || ch == '\n' || ch == '>') {
            if (!current.empty()) lines.push_back(current);
            current.clear();
        } else if (ch != ' ') {
            current += ch;
        }
    }
    if (!current.empty()) lines.push_back(current);
    return lines;
}

bool startsWith(const std::string &line, const char *prefix) {
    size_t prefixLen = strlen(prefix);
    return line.size() >= prefixLen && line.compare(0, prefixLen, prefix) == 0;
}

bool hexByteAt(const std::string &line, size_t pos, long &outByte) {
    if (line.size() < pos + 2) return false;
    if (!isxdigit((unsigned char)line[pos]) || !isxdigit((unsigned char)line[pos + 1])) return false;
    char buf[3] = {line[pos], line[pos + 1], '\0'};
    outByte = strtol(buf, nullptr, 16);
    return true;
}

bool firstTagLine(const char *reply, size_t len, const char *tag, std::string &outLine) {
    for (const std::string &line : strippedLines(reply, len)) {
        if (startsWith(line, tag)) {
            outLine = line;
            return true;
        }
    }
    return false;
}

bool isElmErrorCode(const std::string &line) {
    return line.size() == 5 && startsWith(line, "ERR") && isdigit((unsigned char)line[3]) &&
           isdigit((unsigned char)line[4]);
}

ReplyStatus lineStatus(const std::string &line) {
    if (line == "?") return ReplyStatus::Unknown;
    if (startsWith(line, "NODATA")) return ReplyStatus::NoData;
    if (startsWith(line, "UNABLE")) return ReplyStatus::Unable;
    if (startsWith(line, "STOPPED")) return ReplyStatus::Stopped;
    if (startsWith(line, "CANERROR")) return ReplyStatus::CanError;
    if (startsWith(line, "BUSERROR")) return ReplyStatus::BusError;
    if (startsWith(line, "BUSINIT") && line.find("ERROR") != std::string::npos) return ReplyStatus::BusError;
    if (startsWith(line, "BUFFERFULL")) return ReplyStatus::BufferFull;
    if (isElmErrorCode(line)) return ReplyStatus::ElmError;
    if (line.find("DATAERROR") != std::string::npos) return ReplyStatus::DataError;
    return ReplyStatus::Data;
}

} // namespace

bool isLoneQuestionMark(const char *reply, size_t len) {
    std::vector<std::string> lines = strippedLines(reply, len);
    return lines.size() == 1 && lines[0] == "?";
}

ReplyStatus classifyTerminal(const char *reply, size_t len) {
    for (const std::string &line : strippedLines(reply, len)) {
        ReplyStatus status = lineStatus(line);
        if (status != ReplyStatus::Data) return status;
    }
    return ReplyStatus::Data;
}

bool hasTagLine(const char *reply, size_t len, const char *tag) {
    std::string line;
    return firstTagLine(reply, len, tag, line);
}

ReplyStatus classifyReply(const char *reply, size_t len, const char *tag) {
    bool anyTag = tag == nullptr || tag[0] == '\0';
    if (!anyTag && hasTagLine(reply, len, tag)) return ReplyStatus::Data;
    ReplyStatus terminal = classifyTerminal(reply, len);
    if (terminal != ReplyStatus::Data) return terminal;
    if (anyTag && !strippedLines(reply, len).empty()) return ReplyStatus::Data;
    return ReplyStatus::NoMatch;
}

bool decode1Byte(const char *reply, size_t len, const char *tag, long &outA) {
    std::string line;
    if (!firstTagLine(reply, len, tag, line)) return false;
    return hexByteAt(line, strlen(tag), outA);
}

bool decode2Byte(const char *reply, size_t len, const char *tag, long &outAB) {
    std::string line;
    if (!firstTagLine(reply, len, tag, line)) return false;
    size_t dataStart = strlen(tag);
    long a;
    long b;
    if (!hexByteAt(line, dataStart, a) || !hexByteAt(line, dataStart + 2, b)) return false;
    outAB = a * 256 + b;
    return true;
}

bool decodePercent(const char *reply, size_t len, const char *tag, float &outPercent) {
    long a;
    if (!decode1Byte(reply, len, tag, a)) return false;
    outPercent = percentFromByte(a);
    return true;
}

bool decodeSupportBitmap(const char *reply, size_t len, const char *tag, uint32_t &outBits) {
    const size_t bitmapBytes = 4;
    size_t dataStart = strlen(tag);
    bool anyValid = false;
    uint32_t bits = 0;
    for (const std::string &line : strippedLines(reply, len)) {
        if (!startsWith(line, tag)) continue;
        uint32_t lineBits = 0;
        bool lineValid = true;
        for (size_t i = 0; i < bitmapBytes && lineValid; i++) {
            long byteVal;
            lineValid = hexByteAt(line, dataStart + i * 2, byteVal);
            lineBits = (lineBits << 8) | (uint32_t)byteVal;
        }
        if (!lineValid) continue;
        bits |= lineBits;
        anyValid = true;
    }
    if (anyValid) outBits = bits;
    return anyValid;
}

bool parseBatteryVoltage(const char *reply, size_t len, float &outVolts) {
    for (size_t vIdx = 1; vIdx < len; vIdx++) {
        if (reply[vIdx] != 'V') continue;
        size_t start = vIdx;
        while (start > 0 && (isdigit((unsigned char)reply[start - 1]) || reply[start - 1] == '.')) start--;
        if (start == vIdx) continue;
        std::string number(reply + start, vIdx - start);
        float volts = strtof(number.c_str(), nullptr);
        if (volts < BATTERY_MIN_VOLTS || volts > BATTERY_MAX_VOLTS) return false;
        outVolts = volts;
        return true;
    }
    return false;
}

float percentFromByte(long a) { return a * PERCENT_SCALE / BYTE_FULL_SCALE; }

long rpmFromAB(long ab) { return ab / RPM_DIVISOR; }

float fuelRateLhFromAB(long ab) { return ab / FUEL_RATE_DIVISOR; }

float mafGsFromAB(long ab) { return ab / MAF_DIVISOR; }

float fuelRateLhFromMaf(float mafGs) {
    return mafGs * SECONDS_PER_HOUR / (GASOLINE_STOICH_AFR * GASOLINE_DENSITY_G_PER_L);
}

float updateConsumption(
    float currentLPer100, float defaultLPer100, bool forceDefault, const ConsumptionSample &s
) {
    if (forceDefault) return defaultLPer100;
    if (!s.rateOk || !s.speedOk || s.speedKmh < CONSUMPTION_MIN_SPEED_KMH) return currentLPer100;
    float instant = s.fuelRateLh / s.speedKmh * PERCENT_SCALE;
    if (instant < 0.0f || instant > CONSUMPTION_MAX_INSTANT_L_PER_100) return currentLPer100;
    return CONSUMPTION_EMA_KEEP * currentLPer100 + CONSUMPTION_EMA_NEW * instant;
}

} // namespace obd
