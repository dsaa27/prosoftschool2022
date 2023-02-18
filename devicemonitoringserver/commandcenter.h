#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#include <deviceworkschedule.h>
#include <message.h>
#include <map>
#include <cmath>

struct DeviceInformation {
    unsigned int counter = 0;
    uint64_t lastTimeStamp = 0;
    float MSE = 0;
};

class CommandCenter
{
public:

    void setScheduleMap(const DeviceWorkSchedule& inputWorkSchedule);
    Message * createCommand(uint64_t deviceId, Meterages * const message);
    float calculationMSE(uint64_t deviceId, uint8_t correctionInput);
    float getMSE(uint64_t deviceId);

private:
    std::map<uint64_t, std::vector<Phase>> ScheduleMap;   
    std::map<uint64_t, DeviceInformation> Information;

};

#endif // COMMANDCENTER_H

