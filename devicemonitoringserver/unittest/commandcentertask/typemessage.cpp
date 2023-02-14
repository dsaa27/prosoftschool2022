#include "../unittest.h"
#include "../../test_runner.h"
#include "../../clientservercomponents/message/meteragemessage.h"
#include "../../clientservercomponents/message/errormessage.h"
#include "../../clientservercomponents/message/commandmessage.h"

void unitTest::commandCenterTask::typeMessage::command()
{
    CommandCenter commandCenter;

    uint64_t deviceId = 10213;
    std::vector<Phase> scheduleVector = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}};
    std::vector<Phase> meterageVector = {{0, 1}, {1, 43}, {2, 55}, {3, 15}, {4, 10}, {5, 15}, {6, 10}};
    std::vector<double> expectedCorrections = {0, (1.0 / (43 - 2)), 0, (1.0 / (15 - 53)), (1.0 / (10 - 12)),
                                              (1.0 / (15 - 53)), (1.0 / (10 - 34))};
    std::vector<double> receivedCorrections;
    DeviceWorkSchedule *deviceWorkSchedule = new DeviceWorkSchedule(scheduleVector, deviceId);

    commandCenter.setDeviceWorkSchedule(deviceWorkSchedule);

    MeterageMessage *currentMeterageMessage;
    CommandMessage *currentReceivedMessage;


    currentMeterageMessage = new MeterageMessage({0, 1});
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    receivedCorrections.push_back(currentReceivedMessage->correction);
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({1, 43});
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    receivedCorrections.push_back(currentReceivedMessage->correction);
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({2, 55});
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    receivedCorrections.push_back(currentReceivedMessage->correction);
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({3, 15});
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    receivedCorrections.push_back(currentReceivedMessage->correction);
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({4, 10});
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    receivedCorrections.push_back(currentReceivedMessage->correction);
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({5, 15});
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    receivedCorrections.push_back(currentReceivedMessage->correction);
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({6, 10});
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    receivedCorrections.push_back(currentReceivedMessage->correction);
    delete currentReceivedMessage;


    ASSERT_EQUAL(receivedCorrections, expectedCorrections);

    commandCenter.unsetDeviceWorkSchedule(deviceId);

    delete deviceWorkSchedule;
}

void unitTest::commandCenterTask::typeMessage::catchInvalidArgumentException
    (CommandCenter &commandCenter, uint64_t deviceId,
     std::string &receivedExceptionMessage, AbstractMessage *incorrectFormatMessage)
{
    try {
        commandCenter.receiveAndSendMessage(deviceId, incorrectFormatMessage);
        receivedExceptionMessage = "";
    } catch (std::exception const& ex) {
        receivedExceptionMessage = ex.what();
    }
}

void unitTest::commandCenterTask::typeMessage::incorrectFormat()
{
    using namespace Enumerations;
    CommandCenter commandCenter;

    uint64_t deviceId = 10213;
    std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}, {7, 41}};
    DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

    commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

    AbstractMessage *currentIncorrectFormatMessage;
    std::string exceptionMessage;

    currentIncorrectFormatMessage = new CommandMessage(0.124);
    catchInvalidArgumentException(commandCenter, deviceId, exceptionMessage, currentIncorrectFormatMessage);
    ASSERT_EQUAL(exceptionMessage, "handleMessage has invalid message");

    currentIncorrectFormatMessage = new ErrorMessage(ErrorType::noSchedule);
    catchInvalidArgumentException(commandCenter, deviceId, exceptionMessage, currentIncorrectFormatMessage);
    ASSERT_EQUAL(exceptionMessage, "handleMessage has invalid message");

    currentIncorrectFormatMessage = new ErrorMessage(ErrorType::noTimestamp);
    catchInvalidArgumentException(commandCenter, deviceId, exceptionMessage, currentIncorrectFormatMessage);
    ASSERT_EQUAL(exceptionMessage, "handleMessage has invalid message");

    currentIncorrectFormatMessage = new ErrorMessage(ErrorType::obsolete);
    catchInvalidArgumentException(commandCenter, deviceId, exceptionMessage, currentIncorrectFormatMessage);
    ASSERT_EQUAL(exceptionMessage, "handleMessage has invalid message");

    commandCenter.unsetDeviceWorkSchedule(deviceId);

    delete correctDeviceWorkSchedule;
}

void unitTest::commandCenterTask::typeMessage::noScheduleError()
{
    using namespace Enumerations;
    CommandCenter commandCenter;

    uint64_t deviceId = 41244;
    MeterageMessage *currentMeterageMessage;
    ErrorMessage *currentReceivedMessage;
    ErrorType errorType = ErrorType::noSchedule;

    currentMeterageMessage = new MeterageMessage({0, 1});
    currentReceivedMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    ASSERT_EQUAL(
               static_cast<int>(currentReceivedMessage->errorType),
               static_cast<int>(errorType));
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({234, 62});
    currentReceivedMessage =
           dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    ASSERT_EQUAL(
              static_cast<int>(currentReceivedMessage->errorType),
              static_cast<int>(errorType));
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({12, 2});
    currentReceivedMessage =
          dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    ASSERT_EQUAL(
             static_cast<int>(currentReceivedMessage->errorType),
             static_cast<int>(errorType));

    delete currentReceivedMessage;
}

void unitTest::commandCenterTask::typeMessage::noTimeStampError()
{
    using namespace Enumerations;
    CommandCenter commandCenter;

    uint64_t deviceId = 10213;
    std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}};
    DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

    commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

    ErrorType errorType = ErrorType::noTimestamp;
    MeterageMessage *currentMeterageMessage;
    ErrorMessage *currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({213, 1});
    currentReceivedMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    ASSERT_EQUAL(
               static_cast<int>(currentReceivedMessage->errorType),
               static_cast<int>(errorType));
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({23523, 43});
    currentReceivedMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    ASSERT_EQUAL(
               static_cast<int>(currentReceivedMessage->errorType),
               static_cast<int>(errorType));
    delete currentReceivedMessage;

    currentMeterageMessage = new MeterageMessage({5235, 55});
    currentReceivedMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    ASSERT_EQUAL(
               static_cast<int>(currentReceivedMessage->errorType),
               static_cast<int>(errorType));
    delete currentReceivedMessage;

    commandCenter.unsetDeviceWorkSchedule(deviceId);

    delete correctDeviceWorkSchedule;
}

void unitTest::commandCenterTask::typeMessage::obsoleteError()
{
    using namespace Enumerations;
    CommandCenter commandCenter;

    uint64_t deviceId = 10213;
    std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}, {7, 41}};
    DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

    ErrorType errorType = ErrorType::obsolete;
    MeterageMessage *currentMeterageMessage;
    CommandMessage *currentReceivedCommandMessage;
    ErrorMessage *currentReceivedErrorMessage;

    commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

    currentMeterageMessage = new MeterageMessage({7, 56});
    currentReceivedCommandMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedCommandMessage);
    delete currentReceivedCommandMessage;

    currentMeterageMessage = new MeterageMessage({1, 43});
    currentReceivedErrorMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedErrorMessage);
    ASSERT_EQUAL(
               static_cast<int>(currentReceivedErrorMessage->errorType),
               static_cast<int>(errorType));
    delete currentReceivedErrorMessage;

    currentMeterageMessage = new MeterageMessage({3, 15});
    currentReceivedErrorMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedErrorMessage);
    ASSERT_EQUAL(
               static_cast<int>(currentReceivedErrorMessage->errorType),
               static_cast<int>(errorType));
    delete currentReceivedErrorMessage;

    currentMeterageMessage = new MeterageMessage({4, 10});
    currentReceivedErrorMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedErrorMessage);
    ASSERT_EQUAL(
               static_cast<int>(currentReceivedErrorMessage->errorType),
               static_cast<int>(errorType));
    delete currentReceivedErrorMessage;

    commandCenter.unsetDeviceWorkSchedule(deviceId);

    delete correctDeviceWorkSchedule;
}
