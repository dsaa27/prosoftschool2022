#include "deviceworkschedule.h"

const uint8_t DeviceWorkSchedule::unfoundValue;

DeviceWorkSchedule::DeviceWorkSchedule(const std::vector<Phase> &schedule, uint64_t deviceId)
    : schedule(schedule), deviceId(deviceId) {}

uint8_t DeviceWorkSchedule::findScheduleValue(uint64_t timeStamp)
{
    for (auto now : schedule) {
        if (now.timeStamp == timeStamp) {
            return now.value;
        }
    }
    //return unfoundValue;
    return 255;
}
