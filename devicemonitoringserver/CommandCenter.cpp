#include "CommandCenter.h"
#include "math.h"
int64_t CommandCenter::checkMeterageInPhase(Phase phase, uint64_t deviceId) {
    if (devicesWorkSchedule[deviceId].empty())
        return errorType::NoSchedule;

    Phase phaseFromWorkSchedule = getPhaseFromWorkSchedule(devicesWorkSchedule[deviceId], phase);
    if (phaseFromWorkSchedule.value == 101)
        return errorType::NoTimestamp;

    if (!receivedMeterage.empty() && receivedMeterage.rbegin()->timeStamp > phase.timeStamp)
        return errorType::Obsolete;

    receivedMeterage.insert(phase);

    int64_t diff = 0;

    diff = (int64_t)phaseFromWorkSchedule.value - (int64_t)phase.value;
    devicesDifferenceNeededAndActualValue[deviceId].push_back(diff);
    double sd = countStandardDeviationForPhase(phaseFromWorkSchedule,  deviceId);
    return diff;
}

Phase CommandCenter::getPhaseFromWorkSchedule(std::vector<Phase>& workSchedule, Phase& phase) {
    for (Phase ph : workSchedule)
    {
        if (ph.timeStamp == phase.timeStamp)
            return ph;
    }
    Phase err = {101, 101};
    return err;
}

double CommandCenter::countStandardDeviationForPhase(Phase phase,  uint64_t deviceId) {
    double average = 0;
    double count = (double)devicesDifferenceNeededAndActualValue[deviceId].size();
    for (int64_t v : devicesDifferenceNeededAndActualValue[deviceId])
        average += (double)v;
    average /= count;
    double sum = 0;
    for (int64_t met : devicesDifferenceNeededAndActualValue[deviceId])
        sum += pow(abs((double)met - average), 2);
    sum /= count;
    double standDeviation = sqrt(sum);
    devicesSD[deviceId].push_back(standDeviation);
    return standDeviation;
}

double CommandCenter::getStandardDeviation(uint64_t deviceId) {
    return round(devicesSD[deviceId].back() * 100) / 100;
}

void CommandCenter::addDevice(const DeviceWorkSchedule& workSchedule) {
    if (devicesWorkSchedule.find(workSchedule.deviceId) == devicesWorkSchedule.end())
    {
        devicesWorkSchedule.insert(std::make_pair(workSchedule.deviceId, workSchedule.schedule));
    }
}

void CommandCenter::deleteDevice(uint64_t deviceId) {
    devicesWorkSchedule.erase(deviceId);
}


CommandCenter::CommandCenter()=default;
CommandCenter::~CommandCenter()=default;

