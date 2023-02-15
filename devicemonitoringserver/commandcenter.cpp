#include "commandcenter.h"
#include <deviceworkschedule.h>

void CommandCenter::setScheduleMap(const DeviceWorkSchedule& inputWorkSchedule){

    ScheduleMap[inputWorkSchedule.deviceId] = inputWorkSchedule.schedule;

}

Message * CommandCenter::createCommand(uint64_t deviceId, Meterages * inputMeterage){

    uint64_t maxTimestamp = ScheduleMap[deviceId].back().timeStamp;
    uint64_t minTimestamp = ScheduleMap[deviceId].at(0).timeStamp;
    DeviceWorkSchedule sheduleStruct;

    if (ScheduleMap.find(deviceId) == ScheduleMap.end()) {

        Message * output = new Errors(NoShedule);
        return output;
    } else if (inputMeterage->timeStamp < minTimestamp || inputMeterage->timeStamp > maxTimestamp){

        Message * output = new Errors(NoTimeStamp);
        return output;

    //}  else if (){ здесь проверка на Obsolete

    } else {

        unsigned int numberOfTimestamp;
        for (unsigned int i = 0; sheduleStruct.schedule.size(); i++) {

            if (sheduleStruct.schedule[i].timeStamp == inputMeterage->timeStamp) numberOfTimestamp = i;
        }

        uint8_t correction =  sheduleStruct.schedule[numberOfTimestamp].timeStamp - inputMeterage->value;
        Message * output = new Commands(correction);
    }

}


