#ifndef OBD_PIDS_H
#define OBD_PIDS_H

// Pure ELM327 reply parsing and SAE J1979 decoding, kept Arduino-free for host tests.

#include <cstddef>
#include <cstdint>

namespace obd {

constexpr size_t MAX_REPLY_LEN = 512;

constexpr float PERCENT_SCALE = 100.0f;
constexpr float BYTE_FULL_SCALE = 255.0f;
constexpr long RPM_DIVISOR = 4;
constexpr float FUEL_RATE_DIVISOR = 20.0f;
constexpr float MAF_DIVISOR = 100.0f;
constexpr float GASOLINE_STOICH_AFR = 14.7f;
constexpr float GASOLINE_DENSITY_G_PER_L = 745.0f;
constexpr float SECONDS_PER_HOUR = 3600.0f;
constexpr float BATTERY_MIN_VOLTS = 5.0f;
constexpr float BATTERY_MAX_VOLTS = 20.0f;
constexpr float CONSUMPTION_EMA_KEEP = 0.8f;
constexpr float CONSUMPTION_EMA_NEW = 0.2f;
constexpr long CONSUMPTION_MIN_SPEED_KMH = 3;
constexpr float CONSUMPTION_MAX_INSTANT_L_PER_100 = 60.0f;

enum class ReplyStatus {
    Data,
    NoData,
    Unable,
    Stopped,
    CanError,
    BusError,
    BufferFull,
    ElmError,
    DataError,
    Unknown,
    NoMatch,
};

bool isLoneQuestionMark(const char *reply, size_t len);

// Terminal adapter status found on any reply line, or Data when none is present.
ReplyStatus classifyTerminal(const char *reply, size_t len);

// First reply line (spaces stripped) that starts with tag; an empty tag matches any reply.
bool hasTagLine(const char *reply, size_t len, const char *tag);

// Data before a tag match wins over terminal statuses: another ECU may say NO DATA.
ReplyStatus classifyReply(const char *reply, size_t len, const char *tag);

bool decode1Byte(const char *reply, size_t len, const char *tag, long &outA);
bool decode2Byte(const char *reply, size_t len, const char *tag, long &outAB);
bool decodePercent(const char *reply, size_t len, const char *tag, float &outPercent);

// ORs the 32-bit supported-PID bitmaps of every ECU line that starts with tag.
bool decodeSupportBitmap(const char *reply, size_t len, const char *tag, uint32_t &outBits);

// ATRV replies with the raw voltage text (e.g. "12.6V").
bool parseBatteryVoltage(const char *reply, size_t len, float &outVolts);

float percentFromByte(long a);
long rpmFromAB(long ab);
float fuelRateLhFromAB(long ab);
float mafGsFromAB(long ab);
float fuelRateLhFromMaf(float mafGs);

struct ConsumptionSample {
    bool rateOk;
    float fuelRateLh;
    bool speedOk;
    long speedKmh;
};

// A failed rate sample keeps the current estimate; only forceDefault resets it.
float updateConsumption(
    float currentLPer100, float defaultLPer100, bool forceDefault, const ConsumptionSample &s
);

} // namespace obd

#endif // OBD_PIDS_H
