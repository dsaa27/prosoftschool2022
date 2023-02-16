#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <message/message.h>
#include <map>
#include <cstdint>
#include "deviceworkschedule.h"
#include "devicestatistics.h"

struct Control
{
    int64_t parameterTuning = 0;
    ErrorType errorType = ErrorType::Unknown;
};

struct DeviceData
{
    std::vector<Phase>::iterator iter_schedule;
    const DeviceWorkSchedule* workShedule;
    DeviceStatistics* statistics;
};


class CommandCenter
{
public:
    CommandCenter() = default;
    CommandCenter(const CommandCenter&) = delete;
    CommandCenter(CommandCenter&&) = delete;
    CommandCenter& operator=(const CommandCenter&) = delete;
    CommandCenter& operator=(const CommandCenter&&) = delete;

    Control checkDeviceWorkShedule(uint64_t deviceId, const struct Meterage& meterage);
    bool addDeviceWorkShedule(DeviceWorkSchedule* schedule);
    std::vector<PhaseStatistics> getDeviceStatistics(uint64_t deviceId) const;

    ~CommandCenter();

private:
    bool deviceExist(const uint64_t &deviceId) const;

    std::map<uint64_t, DeviceData> m_devicesData;
};

#endif // COMMANDCENTER_H
