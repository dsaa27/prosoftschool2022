#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "../deviceworkschedule.h"
#include "message/meteragemessage.h"

#include <unordered_map>

class CommandCenter
{
    struct StandardDeviationCalculator
    {
        StandardDeviationCalculator();
        void calculateStandardDeviation ();

        uint64_t lastTimeStamp = 0;
        std::vector<double> inaccuracys;
        double currentStandardDeviation;
    };

public:
    ~CommandCenter();

    //deviceWorkShcedule is now possessing pointer
    void setDeviceWorkSchedule (DeviceWorkSchedule *deviceWorkSchedule);

    //no more posses the pointer of DeviceWorkSchedule
    void unsetDeviceWorkSchedule (uint64_t deviceId);

    DeviceWorkSchedule* getDeviceWorkSchedule (uint64_t deviceId);

    AbstractMessage* receiveAndSendMessage(uint64_t deviceId, AbstractMessage *receivedAbstractMessage);

    double getCurrentStandardDeviation(uint64_t deviceId);

private:
    MeterageMessage* handleMessage(AbstractMessage *receivedAbstractMessage);

    AbstractMessage* makeMessage(uint64_t deviceId, MeterageMessage* handledAbstractMessage);

    AbstractMessage* makeCommandMessage(uint64_t deviceId, MeterageMessage* handledAbstractMessage);

    bool checkNoScheduleError(uint64_t deviceId);

    bool checkNoTimeStampError(uint64_t deviceId, MeterageMessage* handledAbstractMessage);

    bool checkObsolteError(uint64_t deviceId, MeterageMessage* handledAbstractMessage);

private:
    std::unordered_map<uint64_t, DeviceWorkSchedule*> m_schedules;
    std::unordered_map<uint64_t, StandardDeviationCalculator*> m_calculators;
};

#endif // COMMANDCENTER_H
