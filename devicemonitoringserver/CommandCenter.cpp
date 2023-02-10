#include "CommandCenter.h"
#include "math.h"
#include <algorithm>
#include <vector>
#include <iterator>

CommandCenter::CheckResult CommandCenter::checkMeterageInPhase(Phase& phase, uint64_t deviceId) {
    CheckResult result;
    if (m_devicesWorkSchedule[deviceId].empty())
    {
        result.errorCode = errorType::NoSchedule;
        return result;
    }

    std::optional<Phase> phaseFromWorkSchedule = getPhaseFromWorkSchedule(deviceId, phase);
    if (!phaseFromWorkSchedule)
    {
        result.errorCode = errorType::NoTimestamp;
        return result;
    }

    if (!m_receivedMeterage.empty() && (m_receivedMeterage.rbegin()->timeStamp > phase.timeStamp))
    {
        result.errorCode = errorType::Obsolete;
        return result;
    }

    m_receivedMeterage.insert(phase);

    int64_t diff = phaseFromWorkSchedule->value - phase.value;
    m_devicesDifferenceNeededAndActualValue[deviceId].push_back(diff);
    countStandardDeviationForPhase(deviceId);
    result.valueToCorrect = diff;
    return result;
}

std::optional<Phase> CommandCenter::getPhaseFromWorkSchedule(uint64_t deviceId, Phase& phase) {
    for (const Phase& ph : m_devicesWorkSchedule[deviceId])
    {
        if (ph.timeStamp == phase.timeStamp)
            return {ph};
    } 
    return std::nullopt;
}

double CommandCenter::countStandardDeviationForPhase(uint64_t deviceId) {
    double average = 0.0;
    for (int64_t v : m_devicesDifferenceNeededAndActualValue[deviceId])
        average += v;
    double count = m_devicesDifferenceNeededAndActualValue[deviceId].size();
    average /= count;

    double sum = 0;
    for (int64_t met : m_devicesDifferenceNeededAndActualValue[deviceId])
        sum += pow(abs(met - average), 2);
    sum /= count;
    double standDeviation = sqrt(sum);
    m_devicesStandDeviation[deviceId].push_back(standDeviation);
    return standDeviation;
}

double CommandCenter::roundTo2(double value)
{
   return round(value * 100) / 100;
}


double CommandCenter::getStandardDeviation(uint64_t deviceId) {
    if (m_devicesStandDeviation.find(deviceId) == m_devicesStandDeviation.end())
        return 0.0;
    return roundTo2(m_devicesStandDeviation[deviceId].back());
}

void CommandCenter::addDevice(const DeviceWorkSchedule& workSchedule) {
    if (m_devicesWorkSchedule.find(workSchedule.deviceId) == m_devicesWorkSchedule.end())
        m_devicesWorkSchedule.insert(std::make_pair(workSchedule.deviceId, workSchedule.schedule));
}

void CommandCenter::deleteDevice(uint64_t deviceId) {
    if (m_devicesWorkSchedule.find(deviceId) == m_devicesWorkSchedule.end())
        return;
    m_devicesStandDeviation.erase(deviceId);
    m_devicesWorkSchedule.erase(deviceId);
    m_devicesDifferenceNeededAndActualValue.erase(deviceId);
}

