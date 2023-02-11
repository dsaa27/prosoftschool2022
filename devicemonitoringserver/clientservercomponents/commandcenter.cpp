#include "commandcenter.h"
#include "../deviceworkschedule.h"

#include <cmath>

void CommandCenter::setDeviceWorkSchedule(DeviceWorkSchedule *deviceWorkSchedule)
{
    m_schedules[deviceWorkSchedule->deviceId] = deviceWorkSchedule;
    m_calculators[deviceWorkSchedule->deviceId] = new StandardDeviationCalculator();
}

CommandCenter::~CommandCenter()
{
    for (auto it = m_schedules.cbegin(); it != m_schedules.cend(); ++it)
        delete it->second;
    for (auto it = m_calculators.cbegin(); it != m_calculators.cend(); ++it)
        delete it->second;
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

AbstractMessage* CommandCenter::receiveAndSendMessage(uint64_t deviceId, AbstractMessage *receivedAbstractMessage)
{
    MeterageMessage *handledAbstractMessage = handleMessage(receivedAbstractMessage);
    AbstractMessage *madeMessage = makeMessage(deviceId, handledAbstractMessage);
    delete handledAbstractMessage;
    return madeMessage;
}

MeterageMessage* CommandCenter::handleMessage(AbstractMessage *receivedAbstractMessage)
{
    MeterageMessage *receivedMeterageMessage = dynamic_cast<MeterageMessage*>(receivedAbstractMessage);

    if(receivedAbstractMessage) {
        return receivedMeterageMessage;
    } else {
        delete receivedAbstractMessage;
        throw std::invalid_argument("CommandCenter has invalid message");
    }
}

AbstractMessage* CommandCenter::makeMessage(uint64_t deviceId, MeterageMessage* meterageMessage)
{
    AbstractMessage* madeMessage;

    madeMessage = makeNoScheduleMessage(deviceId);
    if(madeMessage)
        return madeMessage;

    madeMessage = makeObsoleteMessage(deviceId, meterageMessage);
    if(madeMessage)
        return madeMessage;

    madeMessage = makeNoTimeStampMessage(deviceId, meterageMessage);
    if(madeMessage)
        return madeMessage;

    madeMessage = makeCommandMessage(deviceId, meterageMessage);
    return madeMessage;
}

AbstractMessage* CommandCenter::makeNoScheduleMessage(uint64_t deviceId)
{
    DeviceWorkSchedule *deviceWorkSchedule = getDeviceWorkSchedule(deviceId);
    if(deviceWorkSchedule) {
        return nullptr;
    } else {
        return new ErrorMessage(Enumerations::ErrorType::noSchedule);
    }
}

AbstractMessage* CommandCenter::makeObsoleteMessage(uint64_t deviceId, MeterageMessage* handledAbstractMessage)
{
    StandardDeviationCalculator *deviceCalculator = m_calculators[deviceId];
    if ((handledAbstractMessage->timeStamp > deviceCalculator->lastTimeStamp)
        ||
        (deviceCalculator->inaccuracys.size() == 0)) {
        return nullptr;
    } else {
        return new ErrorMessage (Enumerations::ErrorType::obsolete);
    }
}

AbstractMessage* CommandCenter::makeNoTimeStampMessage(uint64_t deviceId, MeterageMessage* handledAbstractMessage)
{
    DeviceWorkSchedule *deviceWorkSchedule = getDeviceWorkSchedule(deviceId);
    uint8_t expectedValue = deviceWorkSchedule->findScheduleValue(handledAbstractMessage->timeStamp);
    if (expectedValue == DeviceWorkSchedule::unfoundValue) {
        return new ErrorMessage(Enumerations::ErrorType::noTimestamp);
    } else {
        return nullptr;
    }
}

AbstractMessage* CommandCenter::makeCommandMessage(uint64_t deviceId, MeterageMessage* handledAbstractMessage)
{
    DeviceWorkSchedule *deviceWorkSchedule = getDeviceWorkSchedule(deviceId);
    StandardDeviationCalculator *deviceCalculator = m_calculators[deviceId];
    uint8_t expectedValue = deviceWorkSchedule->findScheduleValue(handledAbstractMessage->timeStamp);
    int inaccuracy = handledAbstractMessage->measureValue - expectedValue;
    double correction = ((inaccuracy == 0) ? 0 : (1.0 / inaccuracy));
    deviceCalculator->inaccuracys.push_back(inaccuracy);
    deviceCalculator->calculateStandartDeviation();
    deviceCalculator->lastTimeStamp = handledAbstractMessage->timeStamp;
    return new CommandMessage(correction);
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
    average /= inaccuracys.size();

    double sumOfSquares = 0;
    for (auto now : inaccuracys)
        sumOfSquares += ((average - now) * (average - now));

    currentSD = sqrt(sumOfSquares / inaccuracys.size());
}

double CommandCenter::getCurrentStandardDeviation(uint64_t deviceId)
{
    return m_calculators[deviceId]->currentSD;
}

