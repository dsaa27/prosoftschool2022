#include "commandcenter.h"

CommandCenter::~CommandCenter()
{
    for (const std::pair<uint64_t, DeviceData>& value : m_devicesData)
    {
        delete value.second.statistics;
        delete value.second.workShedule;
    }
}

Control CommandCenter::checkDeviceWorkShedule(uint64_t deviceId, const struct Meterage& meterage)
{
    if(!deviceExist(deviceId))
        return Control{0, NoSchedule};
    DeviceData deviceData = m_devicesData.at(deviceId);
    auto iter_end = deviceData.workShedule->schedule.end();
    if(deviceData.iter_schedule == iter_end)
        return Control{0, NoTimestamp};
    if(meterage.timeStamp < deviceData.iter_schedule->timeStamp)
        return Control{0, Obsolete};
    std::vector<Phase>::iterator iter_actual = deviceData.iter_schedule;
    while(iter_actual + 1 != iter_end && meterage.timeStamp >= (iter_actual + 1)->timeStamp)
        ++iter_actual;
    int8_t diff = iter_actual->value - meterage.value;
    m_devicesData.at(deviceId).iter_schedule = iter_actual;
    m_devicesData.at(deviceId).statistics->addValue(iter_actual->timeStamp, diff);
    return Control{diff, Unknown};
}

bool CommandCenter::addDeviceWorkShedule(DeviceWorkSchedule* schedule)
{
    if(!schedule || deviceExist(schedule->deviceId))
        return false;
    DeviceData newDevice =
    {
        schedule->schedule.begin(),
        schedule,
        new DeviceStatistics(schedule->deviceId)
    };
    return m_devicesData.insert(std::make_pair(schedule->deviceId, newDevice)).second;
}

std::vector<PhaseStatistics> CommandCenter::getDeviceStatistics(uint64_t deviceId) const
{
    if(!deviceExist(deviceId))
        return std::vector<PhaseStatistics>();
    return m_devicesData.at(deviceId).statistics->getStatistics();
}

bool CommandCenter::deviceExist(const uint64_t &deviceId) const
{
    return m_devicesData.find(deviceId) != m_devicesData.end();
}
