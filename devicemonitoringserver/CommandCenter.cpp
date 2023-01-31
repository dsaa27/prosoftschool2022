#include "CommandCenter.h"

uint8_t CommandCenter::checkMeterageInPhase(Phase& phase, std::vector<Phase>& workSchedule) {
    if (workSchedule.empty())
        return errorType::NoSchedule;

    Phase phaseFromWorkSchedule = getPhaseFromWorkSchedule(workSchedule, phase);
    if (phaseFromWorkSchedule.value == 101)
        return errorType::NoTimestamp;

    if (!receivedMeterage.empty() && receivedMeterage.rbegin()->timeStamp > phase.timeStamp)
        return errorType::Obsolete;

    receivedMeterage.insert(phase);

    uint8_t diff = 0;
    if (phaseFromWorkSchedule.value >= phase.value)
        diff = phaseFromWorkSchedule.value - phase.value;
    else diff = phase.value - phaseFromWorkSchedule.value;
    differenceNeedAndActualValue.push_back(diff);
    //countStandardDeviationForPhase(phase);
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

void CommandCenter::countStandardDeviationForPhase(Phase phase) {
    int64_t average = 0;
    for (uint8_t v : differenceNeedAndActualValue)
        average+= v;
    average /= differenceNeedAndActualValue.size();
    uint64_t sum = 0;
   /* for (Phase phase : receivedMeterage)
    {
        sum += phase.value - average;
    }*/
}

CommandCenter::CommandCenter()=default;
CommandCenter::~CommandCenter()=default;

