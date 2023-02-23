#include "deviceworkschedule.h"

#include <algorithm>

const uint8_t DeviceWorkSchedule::unfoundValue;

DeviceWorkSchedule::DeviceWorkSchedule(const std::vector<Phase> &schedule, uint64_t deviceId)
    : schedule(schedule), deviceId(deviceId) {}

uint8_t DeviceWorkSchedule::findScheduleValue(uint64_t timeStamp)
{
    const auto it = std::find_if(schedule.cbegin(),
                                 schedule.cend(),
                                 [&timeStamp](const Phase& currentPhase){ return currentPhase.timeStamp == timeStamp;});
    return (it == schedule.cend()) ? unfoundValue : (*it).value;
}
