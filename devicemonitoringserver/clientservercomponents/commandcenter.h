#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "../deviceworkschedule.h"
#include "abstractmessage.h"

#include <unordered_map>

class CommandCenter
{
    struct StandardDeviationCalculator
    {
        StandardDeviationCalculator();
        void calculateStandartDeviation ();

        uint64_t lastTimeStamp = 0;
        std::vector<double> inaccuracys;
        double currentSD;
    };

public:
    CommandCenter() = default;
    ~CommandCenter();

    void setDeviceWorkSchedule (DeviceWorkSchedule *deviceWorkSchedule);

    void unsetDeviceWorkSchedule (uint64_t deviceId);

    DeviceWorkSchedule* getDeviceWorkSchedule (uint64_t deviceId);

    AbstractMessage* receiveAndSendMessage(uint64_t deviceId, AbstractMessage *receivedMessage);

    double getCurrentStandardDeviation(uint64_t deviceId);

private:
    std::unordered_map<uint64_t, DeviceWorkSchedule*> m_schedules;
    std::unordered_map<uint64_t, StandardDeviationCalculator*> m_calculators;
};

#endif // COMMANDCENTER_H
