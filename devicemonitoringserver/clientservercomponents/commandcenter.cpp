#include "commandcenter.h"
#include "../deviceworkschedule.h"

#include <cmath>

CommandCenter::~CommandCenter()
{
    for (auto it = m_schedules.cbegin(); it != m_schedules.cend(); ++it)
        delete it->second;
    for (auto it = m_calculators.cbegin(); it != m_calculators.cend(); ++it)
        delete it->second;
}

void CommandCenter::setDeviceWorkSchedule(DeviceWorkSchedule *deviceWorkSchedule)
{
    m_schedules[deviceWorkSchedule->deviceId] = deviceWorkSchedule;
    m_calculators[deviceWorkSchedule->deviceId] = new StandardDeviationCalculator();
}

void CommandCenter::unsetDeviceWorkSchedule (uint64_t deviceId)
{
    m_schedules.erase(deviceId);
    m_calculators.erase(deviceId);
}

DeviceWorkSchedule* CommandCenter::getDeviceWorkSchedule (uint64_t deviceId)
{
    const auto it = m_schedules.find(deviceId);
    return it != m_schedules.cend() ? it->second : nullptr;
}

AbstractMessage* CommandCenter::receiveAndSendMessage(uint64_t deviceId, AbstractMessage *receivedMessage)
{
    MeterageMessage *receivedMeterageMessage = dynamic_cast<MeterageMessage*>(receivedMessage);
    if(receivedMeterageMessage)
    {
        DeviceWorkSchedule *deviceWorkSchedule = getDeviceWorkSchedule(deviceId);
        if (deviceWorkSchedule) {
            StandardDeviationCalculator *deviceCalculator = m_calculators[deviceId];
            if (   (receivedMeterageMessage->timeStamp > deviceCalculator->lastTimeStamp)
                   ||
                   (deviceCalculator->inaccuracys.size() == 0)) {
                uint8_t expectedValue = deviceWorkSchedule->findScheduleValue(receivedMeterageMessage->timeStamp);
                if (expectedValue == DeviceWorkSchedule::unfoundValue) {
                    return new ErrorMessage(Enumerations::ErrorType::noTimestamp);
                } else {
                    int inaccuracy = receivedMeterageMessage->measureValue - expectedValue;
                    double correction = ((inaccuracy == 0) ? 0 : (1.0 / inaccuracy));
                    deviceCalculator->inaccuracys.push_back(inaccuracy);
                    deviceCalculator->calculateStandartDeviation();
                    deviceCalculator->lastTimeStamp = receivedMeterageMessage->timeStamp;
                    return new CommandMessage(correction);
                }
            } else {
                return new ErrorMessage (Enumerations::ErrorType::obsolete);
            }
        } else {
            return new ErrorMessage(Enumerations::ErrorType::noSchedule);
        }
    } else {
        throw std::invalid_argument("receiveAndSentMessage has invalid argument");
        return nullptr;
    }
}

CommandCenter::StandardDeviationCalculator::StandardDeviationCalculator()
{
    lastTimeStamp = 0;
    inaccuracys = std::vector<double>();
    currentSD = 0;
}

void CommandCenter::StandardDeviationCalculator::calculateStandartDeviation()
{
    double average = 0;
    for (auto now : inaccuracys)
        average += now;

    double sumOfSquares = 0;
    for (auto now : inaccuracys)
        sumOfSquares += (average - now) * (average - now);

    currentSD =  sqrt(sumOfSquares / inaccuracys.size());
}

double CommandCenter::getCurrentStandardDeviation(uint64_t deviceId)
{
    return m_calculators[deviceId]->currentSD;
}

