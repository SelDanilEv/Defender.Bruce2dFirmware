#include "modules/obd/obd_poll_scheduler.h"

namespace obd {

uint32_t advanceDue(uint32_t dueMs, uint32_t intervalMs, uint32_t nowMs) {
    uint32_t next = dueMs + intervalMs;
    if ((int32_t)(nowMs - next) > 0) return nowMs;
    return next;
}

int PollScheduler::addTask(uint32_t intervalMs, uint32_t firstDueMs) {
    if (taskCount >= MAX_TASKS) return NONE_DUE;
    intervals[taskCount] = intervalMs;
    dueTimes[taskCount] = firstDueMs;
    return (int)taskCount++;
}

int PollScheduler::pickMostOverdue(uint32_t nowMs) const {
    int picked = NONE_DUE;
    int32_t pickedLateness = 0;
    for (size_t i = 0; i < taskCount; i++) {
        int32_t lateness = (int32_t)(nowMs - dueTimes[i]);
        if (lateness < 0) continue;
        if (picked == NONE_DUE || lateness > pickedLateness) {
            picked = (int)i;
            pickedLateness = lateness;
        }
    }
    return picked;
}

void PollScheduler::markRan(int index, uint32_t nowMs) {
    dueTimes[index] = advanceDue(dueTimes[index], intervals[index], nowMs);
}

void PollScheduler::setInterval(int index, uint32_t intervalMs) { intervals[index] = intervalMs; }

} // namespace obd
