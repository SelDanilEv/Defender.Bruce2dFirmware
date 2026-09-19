#ifndef OBD_POLL_SCHEDULER_H
#define OBD_POLL_SCHEDULER_H

#include <cstddef>
#include <cstdint>

namespace obd {

// Next due time after a run; a task that fell behind is clamped to now instead of bursting.
uint32_t advanceDue(uint32_t dueMs, uint32_t intervalMs, uint32_t nowMs);

class PollScheduler {
public:
    static constexpr size_t MAX_TASKS = 16;
    static constexpr int NONE_DUE = -1;

    int addTask(uint32_t intervalMs, uint32_t firstDueMs);
    int pickMostOverdue(uint32_t nowMs) const;
    void markRan(int index, uint32_t nowMs);
    void setInterval(int index, uint32_t intervalMs);
    uint32_t interval(int index) const { return intervals[index]; }
    uint32_t nextDue(int index) const { return dueTimes[index]; }
    size_t count() const { return taskCount; }

private:
    uint32_t intervals[MAX_TASKS] = {};
    uint32_t dueTimes[MAX_TASKS] = {};
    size_t taskCount = 0;
};

} // namespace obd

#endif // OBD_POLL_SCHEDULER_H
