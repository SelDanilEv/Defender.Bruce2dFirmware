#include "modules/obd/obd_pids.h"
#include "modules/obd/obd_poll_scheduler.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

namespace {

size_t len(const char *text) { return strlen(text); }

bool near(float actual, float expected) { return std::fabs(actual - expected) < 0.01f; }

void testPercentDecode() {
    const char *reply = "41 04 7F\r\r>";
    float percent = 0.0f;
    assert(obd::decodePercent(reply, len(reply), "4104", percent));
    assert(near(percent, 127 * 100.0f / 255.0f));

    const char *full = "4111FF\r>";
    assert(obd::decodePercent(full, len(full), "4111", percent));
    assert(near(percent, 100.0f));
}

void testRpmTwoByteDecode() {
    const char *reply = "410C1AF8\r\r>";
    long ab = 0;
    assert(obd::decode2Byte(reply, len(reply), "410C", ab));
    assert(ab == 0x1AF8);
    assert(obd::rpmFromAB(ab) == 0x1AF8 / 4);
}

void testSpeedOneByteDecode() {
    const char *reply = "41 0D 3C \r\r>";
    long speed = 0;
    assert(obd::decode1Byte(reply, len(reply), "410D", speed));
    assert(speed == 60);
}

void testBatteryVoltage() {
    const char *ok = "14.6V\r\r>";
    float volts = 0.0f;
    assert(obd::parseBatteryVoltage(ok, len(ok), volts));
    assert(near(volts, 14.6f));

    const char *tooHigh = "24.1V\r\r>";
    volts = 0.0f;
    assert(!obd::parseBatteryVoltage(tooHigh, len(tooHigh), volts));
    assert(volts == 0.0f);

    const char *tooLow = "2.0V\r>";
    assert(!obd::parseBatteryVoltage(tooLow, len(tooLow), volts));

    const char *noNumber = "ATRV\r?\r>";
    assert(!obd::parseBatteryVoltage(noNumber, len(noNumber), volts));
}

void testTerminalStatusClassification() {
    struct Case {
        const char *reply;
        obd::ReplyStatus expected;
    };
    const Case cases[] = {
        {"NO DATA\r\r>",                       obd::ReplyStatus::NoData    },
        {"SEARCHING...\rUNABLE TO CONNECT\r>", obd::ReplyStatus::Unable    },
        {"STOPPED\r\r>",                       obd::ReplyStatus::Stopped   },
        {"CAN ERROR\r\r>",                     obd::ReplyStatus::CanError  },
        {"BUS INIT: ...ERROR\r>",              obd::ReplyStatus::BusError  },
        {"BUS ERROR\r>",                       obd::ReplyStatus::BusError  },
        {"BUFFER FULL\r>",                     obd::ReplyStatus::BufferFull},
        {"ERR94\r>",                           obd::ReplyStatus::ElmError  },
        {"<DATA ERROR\r>",                     obd::ReplyStatus::DataError },
        {"?\r\r>",                             obd::ReplyStatus::Unknown   },
    };
    for (const Case &testCase : cases) {
        assert(obd::classifyReply(testCase.reply, len(testCase.reply), "4104") == testCase.expected);
        float percent = 0.0f;
        assert(!obd::decodePercent(testCase.reply, len(testCase.reply), "4104", percent));
    }

    const char *data = "410457\r\r>";
    assert(obd::classifyReply(data, len(data), "4104") == obd::ReplyStatus::Data);
    const char *otherPid = "410C1AF8\r\r>";
    assert(obd::classifyReply(otherPid, len(otherPid), "4104") == obd::ReplyStatus::NoMatch);
    const char *atReply = "OK\r\r>";
    assert(obd::classifyReply(atReply, len(atReply), "") == obd::ReplyStatus::Data);
    const char *secondEcuNoData = "410457\rNO DATA\r>";
    assert(obd::classifyReply(secondEcuNoData, len(secondEcuNoData), "4104") == obd::ReplyStatus::Data);
}

void testLoneQuestionMark() {
    const char *lone = "?\r\r>";
    assert(obd::isLoneQuestionMark(lone, len(lone)));
    const char *loneLeadingCr = "\r?\r\r>";
    assert(obd::isLoneQuestionMark(loneLeadingCr, len(loneLeadingCr)));
    const char *embedded = "ATE0\r?\r\r>";
    assert(!obd::isLoneQuestionMark(embedded, len(embedded)));
    const char *insideData = "41 04 ?\r>";
    assert(!obd::isLoneQuestionMark(insideData, len(insideData)));
    assert(obd::classifyTerminal(insideData, len(insideData)) == obd::ReplyStatus::Data);
}

void testTruncatedAndNonHexRejected() {
    const char *truncated = "4104\r\r>";
    float percent = 42.0f;
    assert(!obd::decodePercent(truncated, len(truncated), "4104", percent));
    assert(percent == 42.0f);

    const char *halfByte = "41045\r>";
    assert(!obd::decodePercent(halfByte, len(halfByte), "4104", percent));

    const char *nonHex = "4104ZZ\r>";
    assert(!obd::decodePercent(nonHex, len(nonHex), "4104", percent));

    const char *truncatedTwoByte = "410C1A\r>";
    long ab = 7;
    assert(!obd::decode2Byte(truncatedTwoByte, len(truncatedTwoByte), "410C", ab));
    assert(ab == 7);

    const char *nonHexSecond = "410C1AG0\r>";
    assert(!obd::decode2Byte(nonHexSecond, len(nonHexSecond), "410C", ab));
}

void testTagMatchedOnlyAtLineStart() {
    const char *reply = "410C4104AA\r\r>";
    float percent = 0.0f;
    assert(!obd::decodePercent(reply, len(reply), "4104", percent));
    assert(!obd::hasTagLine(reply, len(reply), "4104"));

    const char *echoed = "0104\r4104 33\r\r>";
    assert(obd::decodePercent(echoed, len(echoed), "4104", percent));
    assert(near(percent, 0x33 * 100.0f / 255.0f));
}

void testMultiEcuValuesUseFirstLine() {
    const char *reply = "410440\r410480\r\r>";
    long a = 0;
    assert(obd::decode1Byte(reply, len(reply), "4104", a));
    assert(a == 0x40);
}

void testMultiEcuBitmapOr() {
    const char *reply = "4100BFBEB993\r410098180001\r\r>";
    uint32_t bits = 0;
    assert(obd::decodeSupportBitmap(reply, len(reply), "4100", bits));
    assert(bits == (0xBFBEB993u | 0x98180001u));

    const char *oneValid = "4100BFBE\r410098180001\r>";
    assert(obd::decodeSupportBitmap(oneValid, len(oneValid), "4100", bits));
    assert(bits == 0x98180001u);

    const char *noneValid = "NO DATA\r>";
    bits = 5;
    assert(!obd::decodeSupportBitmap(noneValid, len(noneValid), "4100", bits));
    assert(bits == 5);
}

void testFuelFormulas() {
    assert(near(obd::fuelRateLhFromAB(0x00C8), 10.0f));
    assert(near(obd::mafGsFromAB(0x03E8), 10.0f));
    assert(near(obd::fuelRateLhFromMaf(10.0f), 10.0f * 3600.0f / (14.7f * 745.0f)));
}

void testConsumption() {
    obd::ConsumptionSample moving = {true, 6.0f, true, 100};
    float updated = obd::updateConsumption(8.0f, 8.0f, false, moving);
    assert(near(updated, 0.8f * 8.0f + 0.2f * 6.0f));

    assert(near(obd::updateConsumption(9.5f, 8.0f, true, moving), 8.0f));

    obd::ConsumptionSample rateFailed = {false, 0.0f, true, 100};
    assert(near(obd::updateConsumption(9.5f, 8.0f, false, rateFailed), 9.5f));

    obd::ConsumptionSample tooSlow = {true, 6.0f, true, 2};
    assert(near(obd::updateConsumption(9.5f, 8.0f, false, tooSlow), 9.5f));

    obd::ConsumptionSample speedFailed = {true, 6.0f, false, 0};
    assert(near(obd::updateConsumption(9.5f, 8.0f, false, speedFailed), 9.5f));

    obd::ConsumptionSample implausible = {true, 70.0f, true, 100};
    assert(near(obd::updateConsumption(9.5f, 8.0f, false, implausible), 9.5f));
}

void testSchedulerPicksMostOverdue() {
    obd::PollScheduler scheduler;
    int fast = scheduler.addTask(500, 1000);
    int slow = scheduler.addTask(5000, 400);
    int later = scheduler.addTask(500, 3000);

    assert(scheduler.pickMostOverdue(300) == obd::PollScheduler::NONE_DUE);
    assert(scheduler.pickMostOverdue(1200) == slow);
    scheduler.markRan(slow, 1200);
    assert(scheduler.nextDue(slow) == 5400);
    assert(scheduler.pickMostOverdue(1200) == fast);
    assert(later == 2);
}

void testSchedulerCatchUpClampAndRollover() {
    assert(obd::advanceDue(1000, 500, 1200) == 1500);
    assert(obd::advanceDue(1000, 500, 4000) == 4000);

    const uint32_t nearWrap = 0xFFFFFF00u;
    assert(obd::advanceDue(nearWrap, 0x200, nearWrap + 0x10) == nearWrap + 0x200);

    obd::PollScheduler scheduler;
    int wrapped = scheduler.addTask(500, 0x00000010u);
    int beforeWrap = scheduler.addTask(500, 0xFFFFFFF0u);
    assert(scheduler.pickMostOverdue(0x00000020u) == beforeWrap);
    scheduler.markRan(beforeWrap, 0x00000020u);
    assert(scheduler.pickMostOverdue(0x00000020u) == wrapped);
    assert(scheduler.pickMostOverdue(0xFFFFFFF0u) == obd::PollScheduler::NONE_DUE);
}

void testSchedulerIntervalChangeIsPerTask() {
    obd::PollScheduler scheduler;
    int fuelLevel = scheduler.addTask(5000, 0);
    int consumption = scheduler.addTask(5000, 0);
    scheduler.setInterval(fuelLevel, 60000);
    scheduler.markRan(fuelLevel, 10);
    scheduler.markRan(consumption, 10);
    assert(scheduler.nextDue(fuelLevel) == 60000);
    assert(scheduler.nextDue(consumption) == 5000);
}

} // namespace

int main() {
    testPercentDecode();
    testRpmTwoByteDecode();
    testSpeedOneByteDecode();
    testBatteryVoltage();
    testTerminalStatusClassification();
    testLoneQuestionMark();
    testTruncatedAndNonHexRejected();
    testTagMatchedOnlyAtLineStart();
    testMultiEcuValuesUseFirstLine();
    testMultiEcuBitmapOr();
    testFuelFormulas();
    testConsumption();
    testSchedulerPicksMostOverdue();
    testSchedulerCatchUpClampAndRollover();
    testSchedulerIntervalChangeIsPerTask();
    printf("obd_pids_test: all tests passed\n");
    return 0;
}
