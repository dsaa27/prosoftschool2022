#include "commandcenter.h"
#include "../deviceworkschedule.h"
#include "message/meteragemessage.h"
#include "message/errormessage.h"
#include "message/commandmessage.h"

#include <cmath>
#include <iostream>

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
    //no leak, cause schedule must delete now the creator of it
    m_schedules.erase(deviceId);
    //created here and delete here aswell
    delete m_calculators[deviceId];
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

    if(receivedMeterageMessage) {
        return receivedMeterageMessage;
    } else {
        delete receivedAbstractMessage;
        throw std::invalid_argument("handleMessage has invalid message");
    }
}

AbstractMessage* CommandCenter::makeMessage(uint64_t deviceId, MeterageMessage* meterageMessage)
{
    if(checkNoScheduleError(deviceId))
        return new ErrorMessage(Enumerations::ErrorType::noSchedule);

    if(checkNoTimeStampError(deviceId, meterageMessage))
        return new ErrorMessage(Enumerations::ErrorType::noTimestamp);

    if(checkObsolteError(deviceId, meterageMessage))
        return new ErrorMessage (Enumerations::ErrorType::obsolete);

    return makeCommandMessage(deviceId, meterageMessage);
}

bool CommandCenter::checkNoScheduleError(uint64_t deviceId)
{
    DeviceWorkSchedule *deviceWorkSchedule = getDeviceWorkSchedule(deviceId);
    return ((deviceWorkSchedule) ? false : true);
}

bool CommandCenter::checkNoTimeStampError(uint64_t deviceId, MeterageMessage* handledAbstractMessage)
{
    DeviceWorkSchedule *deviceWorkSchedule = getDeviceWorkSchedule(deviceId);
    uint8_t expectedValue = deviceWorkSchedule->findScheduleValue(handledAbstractMessage->timeStamp);
    return ((expectedValue == DeviceWorkSchedule::unfoundValue) ? true : false);
}

bool CommandCenter::checkObsolteError(uint64_t deviceId, MeterageMessage* handledAbstractMessage)
{
    StandardDeviationCalculator *deviceCalculator = m_calculators[deviceId];
    if ((handledAbstractMessage->timeStamp > deviceCalculator->lastTimeStamp) || (deviceCalculator->inaccuracys.size() == 0)) {
        return false;
    } else {
        return true;
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
    deviceCalculator->calculateStandardDeviation();
    deviceCalculator->lastTimeStamp = handledAbstractMessage->timeStamp;
    return new CommandMessage(correction);
}

CommandCenter::StandardDeviationCalculator::StandardDeviationCalculator()
{
    lastTimeStamp = 0;
    inaccuracys = std::vector<double>();
    currentStandardDeviation = 0;
}

void CommandCenter::StandardDeviationCalculator::calculateStandardDeviation()
{
    double average = 0;
    for (const auto now : inaccuracys)
        average += now;
    average /= inaccuracys.size();

    double sumOfSquares = 0;
    for (const auto now : inaccuracys)
        sumOfSquares += ((average - now) * (average - now));

    currentStandardDeviation = sqrt(sumOfSquares / inaccuracys.size());
}

double CommandCenter::getCurrentStandardDeviation(uint64_t deviceId)
{
    return m_calculators[deviceId]->currentStandardDeviation;
}

