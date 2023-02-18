#include "commandcenter.h"
#include <deviceworkschedule.h>

void CommandCenter::setScheduleMap(const DeviceWorkSchedule& inputWorkSchedule){

    ScheduleMap[inputWorkSchedule.deviceId] = inputWorkSchedule.schedule;

}

Message * CommandCenter::createCommand(uint64_t deviceId, Meterages * const inputMeterage){

    uint64_t maxTimestamp = ScheduleMap[deviceId].back().timeStamp;
    uint64_t minTimestamp = ScheduleMap[deviceId].at(0).timeStamp;
    DeviceWorkSchedule sheduleStruct;

    if (ScheduleMap.find(deviceId) == ScheduleMap.end()) {

        Message * output = new Errors(NoShedule);
        return output;
    } else if (inputMeterage->timeStamp < minTimestamp || inputMeterage->timeStamp > maxTimestamp){

        Message * output = new Errors(NoTimeStamp);
        return output;
    }  else if (inputMeterage->timeStamp < Information[deviceId].lastTimeStamp){
        Message * output = new Errors(Obsolete);
        return output;
    } else { //отправка команды, запись последней метки времени, расчет СКО

        unsigned int numberOfTimestamp = 0;
        for (unsigned int i = 0; sheduleStruct.schedule.size(); i++) {

            if (sheduleStruct.schedule[i].timeStamp == inputMeterage->timeStamp) numberOfTimestamp = i;
        }
        uint8_t correction =  sheduleStruct.schedule[numberOfTimestamp].timeStamp - inputMeterage->value; //расчет корректировки
        Message * output = new Commands(correction);
        Information[deviceId].lastTimeStamp = inputMeterage->timeStamp; //установка текущей метки времени в качестве последней для текущего устройства
        Information[deviceId].MSE = calculationMSE(deviceId, correction);
        Information[deviceId].counter++;

        return output;

    }   
}
float CommandCenter::calculationMSE(uint64_t deviceId, uint8_t correctionInput){

    float buf1 = correctionInput;
    float MSE = Information[deviceId].MSE;
    float outputMSE;
    unsigned int counter = Information[deviceId].counter;

    outputMSE = sqrt((pow(MSE, 2) * counter + pow(buf1, 2))/(counter + 1));
    return outputMSE;
}

float CommandCenter::getMSE(uint64_t deviceId){
    return Information[deviceId].MSE;
}

