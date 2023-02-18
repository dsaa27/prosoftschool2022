#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "deviceworkschedule.h"
#include "devicestatistics.h"
#include "common.h"

#include <message/message.h>
#include <map>
#include <cstdint>

struct Control
{
    int64_t parameterTuning = 0;
    ErrorType errorType = ErrorType::eUnknown;
};

struct DeviceData
{
    std::vector<Phase>::iterator iterSchedule;
    uint64_t lastTimeStamp;
    const DeviceWorkSchedule* workSchedule;
    DeviceStatistics* statistics;
};


class CommandCenter
{
    NON_COPYABLE(CommandCenter);
public:
    CommandCenter() = default;

    Control checkDeviceWorkShedule(uint64_t deviceId, const Meterage& meterage);
    bool addDeviceWorkShedule(DeviceWorkSchedule* schedule);
    std::vector<PhaseStatistics> getDeviceStatistics(uint64_t deviceId) const;

    ~CommandCenter();

private:
    constexpr static const Control NOSCHEDULE = Control{0, ErrorType::eNoSchedule};
    constexpr static const Control NOTIMESTMAPS = Control{0, ErrorType::eNoTimestamp};
    constexpr static const Control OBSOLETE = Control{0, ErrorType::eObsolete};

    bool deviceExist(const uint64_t &deviceId) const;

    std::map<uint64_t, DeviceData> m_devicesData;
};

#endif // COMMANDCENTER_H
