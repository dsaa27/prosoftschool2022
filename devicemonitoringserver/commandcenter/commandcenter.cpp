#include "commandcenter.h"


Control::Control(ErrorType errorType) :
    parameterTuning(0), errorType(errorType)
{}

Control::Control(int64_t parameterTuning) :
    parameterTuning(parameterTuning), errorType(ErrorType::eUnknown)
{}


const Control CommandCenter::NOSCHEDULE{ErrorType::eNoSchedule};
const Control CommandCenter::NOTIMESTMAPS{ErrorType::eNoTimestamp};
const Control CommandCenter::OBSOLETE{ErrorType::eObsolete};

CommandCenter::~CommandCenter()
{
    for (const std::pair<uint64_t, DeviceData>& value : m_devicesData)
    {
        delete value.second.statistics;
        delete value.second.workSchedule;
    }
}

Control CommandCenter::checkDeviceWorkShedule(uint64_t deviceId, const Meterage& meterage)
{
    if(!deviceExist(deviceId))
        return NOSCHEDULE;
    DeviceData deviceData = m_devicesData.at(deviceId);
    auto iter_end = deviceData.workSchedule->schedule.end();
    if(deviceData.iterSchedule == iter_end
            || (meterage.timeStamp < deviceData.iterSchedule->timeStamp && deviceData.lastTimeStamp == 0))
        return NOTIMESTMAPS;
    if(meterage.timeStamp < deviceData.lastTimeStamp)
        return OBSOLETE;
    std::vector<Phase>::iterator iter_actual = deviceData.iterSchedule;
    while(iter_actual + 1 != iter_end && meterage.timeStamp >= (iter_actual + 1)->timeStamp)
        ++iter_actual;
    int8_t diff = iter_actual->value - meterage.value;
    m_devicesData.at(deviceId).iterSchedule = iter_actual;
    if(m_devicesData.at(deviceId).statistics->addValue(iter_actual->timeStamp, diff))
    {
        m_devicesData.at(deviceId).lastTimeStamp = meterage.timeStamp;
        return Control{diff};
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
