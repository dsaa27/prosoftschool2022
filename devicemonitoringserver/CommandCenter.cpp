#include "CommandCenter.h"

uint64_t CommandCenter::compareMeterage(Phase meterage, DeviceWorkSchedule* workSchedule) const {
    if (workSchedule == nullptr)
        return errorType::NoSchedule;

    Phase* meterageInWorkSchedule = getPhaseFromWorkSchedule(workSchedule, meterage);
    if (meterageInWorkSchedule == nullptr)
        return errorType::NoTimestamp;

    if (receivedMeterage.rbegin()->timeStamp < meterage.timeStamp)
        return errorType::Obsolete;

    if (meterageInWorkSchedule->timeStamp >= meterage.timeStamp)
        return meterageInWorkSchedule->timeStamp - meterage.timeStamp;
    else return meterage.timeStamp - meterageInWorkSchedule->timeStamp;
}

CommandCenter::CommandCenter()=default;
CommandCenter::~CommandCenter() =default;

