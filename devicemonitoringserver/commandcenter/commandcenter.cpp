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
        return NOSCHEDULE;
    DeviceData deviceData = m_devicesData.at(deviceId);
    auto iter_end = deviceData.workShedule->schedule.end();
    if(deviceData.iter_schedule == iter_end
            || (meterage.timeStamp < deviceData.iter_schedule->timeStamp && deviceData.lastTimeStamp == 0))
        return NOTIMESTMAPS;
    if(meterage.timeStamp < deviceData.lastTimeStamp)
        return OBSOLETE;
    std::vector<Phase>::iterator iter_actual = deviceData.iter_schedule;
    while(iter_actual + 1 != iter_end && meterage.timeStamp >= (iter_actual + 1)->timeStamp)
        ++iter_actual;
    int8_t diff = iter_actual->value - meterage.value;
    m_devicesData.at(deviceId).iter_schedule = iter_actual;
    if(m_devicesData.at(deviceId).statistics->addValue(iter_actual->timeStamp, diff))
    {
        m_devicesData.at(deviceId).lastTimeStamp = meterage.timeStamp;
        return Control{diff, Unknown};
    }
    else
        return OBSOLETE;
}

bool CommandCenter::addDeviceWorkShedule(DeviceWorkSchedule* schedule)
{
    if(!schedule || deviceExist(schedule->deviceId))
        return false;
    DeviceData newDevice =
    {
        schedule->schedule.begin(),
        0,
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
