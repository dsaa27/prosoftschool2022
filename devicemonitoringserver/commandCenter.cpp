#include "commandCenter.h"
#include <iostream>

void CommandCenter::setSchedule(const DeviceWorkSchedule& deviceWorkSchedule)
{
    m_scheduleMap[deviceWorkSchedule.deviceId] = deviceWorkSchedule.schedule;
}

MessageStruct CommandCenter::generateCommand(uint64_t deviceId, MessageStruct message)
{
    MessageStruct answer;
    if (m_scheduleMap.find(deviceId) == m_scheduleMap.end())
    {
        answer.messageType = ERROR;
        answer.errorType = NO_SCHEDULE;
        return answer;
    }

    uint64_t& currentTime = message.measurements.timeStamp;
    uint64_t& minTimeStamp = m_scheduleMap[deviceId].at(0).timeStamp;
    uint64_t& maxTimeStamp = m_scheduleMap[deviceId].back().timeStamp;
    if ((currentTime < minTimeStamp) || (currentTime > maxTimeStamp))
    {
        answer.messageType = ERROR;
        answer.errorType = NO_TIMESTAMP;
        return answer;
    }

    if (message.measurements.timeStamp < deviceInfoMap[deviceId].m_lastTimestamp)
    {
        answer.messageType = ERROR;
        answer.errorType = OBSOLETE;
        return answer;
    }

    std::vector<Phase>& schedule = m_scheduleMap[deviceId];
    unsigned int i;
    //Поиск соответсвующей метки начала этапа
    for (i = 0; i < schedule.size(); i++)
    {
        if (schedule[i].timeStamp >= currentTime)
        {
            if (schedule[i].timeStamp > currentTime)
                i--;
            break;
        }
    }
    answer.messageType = COMMAND;
    answer.adjustment = schedule.at(i).value - message.measurements.value;

    updateMse(deviceId, answer.adjustment);
    deviceInfoMap[deviceId].m_lastTimestamp = currentTime;
    deviceInfoMap[deviceId].m_countCommand++;
    return answer;
}

float CommandCenter::getMse(uint64_t deviceId)
{
    if (deviceInfoMap.find(deviceId) == deviceInfoMap.end())
        return 0;
    return deviceInfoMap[deviceId].m_mse;
}

void CommandCenter::updateMse(uint64_t deviceId, int dx)
{
    if (deviceInfoMap.find(deviceId) == deviceInfoMap.end())
        return;
    float& mse = deviceInfoMap[deviceId].m_mse;
    uint64_t& commandCount = deviceInfoMap[deviceId].m_countCommand;
    mse = sqrt((pow(mse, 2) * commandCount + pow(dx, 2))/(commandCount + 1));
}
