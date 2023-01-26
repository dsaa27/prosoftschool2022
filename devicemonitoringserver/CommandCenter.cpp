#include "CommandCenter.h"

//TODO: ско ошибки управления параметром на каждом этапе
uint8_t CommandCenter::checkMeterageInPhase(Phase& phase, std::vector<Phase>& workSchedule) {
    if (workSchedule.empty())
        return errorType::NoSchedule;

    Phase meterageInWorkSchedule = getPhaseFromWorkSchedule(workSchedule, phase);
    if (meterageInWorkSchedule.value == 101)
        return errorType::NoTimestamp;

    if (!receivedMeterage.empty() && receivedMeterage.rbegin()->timeStamp < phase.timeStamp)
        return errorType::Obsolete;

    receivedMeterage.insert(phase);

    if (meterageInWorkSchedule.value >= phase.value)
        return meterageInWorkSchedule.value - phase.value;
    else return phase.value - meterageInWorkSchedule.value;
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

CommandCenter::CommandCenter()=default;
CommandCenter::~CommandCenter()=default;

