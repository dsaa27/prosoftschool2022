#include "CommandCenter.h"

//TODO: ско ошибки управления параметром на каждом этапе
uint8_t CommandCenter::compareMeterage(Phase& meterage, std::vector<Phase>& workSchedule) {
    if (workSchedule.empty())
        return errorType::NoSchedule;

    Phase meterageInWorkSchedule = getPhaseFromWorkSchedule(workSchedule, meterage);
    if (meterageInWorkSchedule.value == 101)
        return errorType::NoTimestamp;

    if (receivedMeterage.rbegin()->timeStamp < meterage.timeStamp)
        return errorType::Obsolete;

    receivedMeterage.insert(meterage);

    if (meterageInWorkSchedule.value >= meterage.value)
        return meterageInWorkSchedule.value - meterage.value;
    else return meterage.value - meterageInWorkSchedule.value;
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

