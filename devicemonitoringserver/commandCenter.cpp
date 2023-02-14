#include "commandCenter.h"

void CommandCenter::setSchedule(const DeviceWorkSchedule& deviceWorkSchedule)
{
    m_scheduleMap[deviceWorkSchedule.deviceId] = deviceWorkSchedule.schedule;
}

MessageStruct CommandCenter::createCommand(uint64_t deviceId, MessageStruct message)
{
    if (m_scheduleMap.find(deviceId) == m_scheduleMap.end())
    {
        MessageStruct answer{NO_SCHEDULE};
        return answer;
    }

    const uint64_t& currentTime = message.measurements.timeStamp;
    if (const uint64_t& minTimeStamp = m_scheduleMap[deviceId].at(0).timeStamp,
                        maxTimeStamp = m_scheduleMap[deviceId].back().timeStamp;
        (currentTime < minTimeStamp) || (currentTime > maxTimeStamp))
    {
        MessageStruct answer{NO_TIMESTAMP};
        return answer;
    }
    DeviceInfo& deviceInfo = deviceInfoMap[deviceId];
    if (message.measurements.timeStamp < deviceInfo.lastTimestamp)
    {
        MessageStruct answer{OBSOLETE};
        return answer;
    }

    const std::vector<Phase>& schedule = m_scheduleMap[deviceId];
    unsigned int i;
    //Поиск соответствующей метки начала этапа
    const uint64_t scheduleSize = schedule.size();
    for (i = 0; i < scheduleSize; ++i)
    {
        if (schedule[i].timeStamp >= currentTime)
        {
            if (schedule[i].timeStamp > currentTime)
                --i;
            break;
        }
    }
    adjustment_t adj = schedule[i].value - message.measurements.value;
    MessageStruct answer{adj};

    updateMse(deviceId, answer.adjustment);
    deviceInfo.lastTimestamp = currentTime;
    deviceInfo.countCommand++;
    return answer;
}

float CommandCenter::getMse(uint64_t deviceId)
{
    if (deviceInfoMap.find(deviceId) == deviceInfoMap.end())
        return 0;
    return deviceInfoMap[deviceId].mse;
}

void CommandCenter::updateMse(uint64_t deviceId, int dx)
{
    if (deviceInfoMap.find(deviceId) == deviceInfoMap.end())
        return;
    DeviceInfo& deviceInfo = deviceInfoMap[deviceId];
    float& mse = deviceInfo.mse;
    const uint64_t& commandCount = deviceInfo.countCommand;
    mse = sqrt((pow(mse, 2) * commandCount + pow(dx, 2))/(commandCount + 1));
}
