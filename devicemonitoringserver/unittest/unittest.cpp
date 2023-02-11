#include "../test_runner.h"
#include "../clientservercomponents/abstractmessage.h"
#include "unittest.h"
#include "../clientservercomponents/commandcenter.h"

#include <random>

void unitTest::messageSerializer()
{
    unitTest::messageSerialization();
    unitTest::messageDeserialization();
}

void unitTest::messageSerialization()
{
    serialization::meterageMessage();
    serialization::commandMessage();
    serialization::errorMessage();
}

void unitTest::messageDeserialization()
{
    deserialization::meterageMessage();
    deserialization::commandMessage();
    deserialization::errorMessage();
    deserialization::invalidArgument();
}

void unitTest::messageEncoder()
{
    codeAlgorithm::MirrorCode();
    codeAlgorithm::Multiply41Code();
    codeAlgorithm::ROT3Code();
    codeAlgorithm::MixedCodeAlgorithms();
    codeAlgorithm::inductiveEncoding();
}

void unitTest::commandCenter()
{
    //testCommandCenterSetUnsetDeviceWorkSchedule();
    //testCommandCenterReceiveAndSendMessage();
    //testStandardDeviationCalculation();
}

void  sendOneCommandMessage
    (CommandCenter &commandCenter,
     uint64_t deviceId,
     Phase schedulePhase,
     Phase meteragePhase)
{
    MeterageMessage *currentMeterageMessage;
    CommandMessage *currentReceivedMessage;
    double correctCorrectionValue;

    currentMeterageMessage = new MeterageMessage(meteragePhase.timeStamp, meteragePhase.value);
    currentReceivedMessage =
            dynamic_cast<CommandMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
    if ((meteragePhase.value - schedulePhase.value) == 0) {
        correctCorrectionValue = 0;
    } else {
        correctCorrectionValue = (1.0 / (meteragePhase.value - schedulePhase.value));
    }
    ASSERT_EQUAL(currentReceivedMessage->correction, correctCorrectionValue);
    delete currentMeterageMessage;
    delete currentReceivedMessage;
}


void unitTest::testCommandtMessage()
{
    CommandCenter commandCenter;

    uint64_t deviceId = 10213;
    std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}};
    DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

    commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

    sendOneCommandMessage(commandCenter, deviceId, {0, 1}, {0, 1});
    sendOneCommandMessage(commandCenter, deviceId, {1, 2}, {1, 43});
    sendOneCommandMessage(commandCenter, deviceId, {2, 55}, {2, 55});
    sendOneCommandMessage(commandCenter, deviceId, {3, 53}, {3, 15});
    sendOneCommandMessage(commandCenter, deviceId, {4, 12}, {4, 10});
    sendOneCommandMessage(commandCenter, deviceId, {5, 53}, {5, 15});
    sendOneCommandMessage(commandCenter, deviceId, {6, 34}, {6, 10});

    commandCenter.unsetDeviceWorkSchedule(deviceId);

    delete correctDeviceWorkSchedule;
}

void sendOneErrorMessage
    (CommandCenter &commandCenter,
     uint64_t deviceId,
     Phase schedulePhase,
     Phase meteragePhase,
     Enumerations::ErrorType errorType)
{
    MeterageMessage *currentMeterageMessage;
    ErrorMessage *currentReceivedMessage;
    double correctCorrectionValue;

    currentMeterageMessage = new MeterageMessage(meteragePhase.timeStamp, meteragePhase.value);
    currentReceivedMessage =
            dynamic_cast<ErrorMessage*>(commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage));
    ASSERT(currentReceivedMessage);
   ASSERT_EQUAL(
               static_cast<int>(currentReceivedMessage->errorType),
               static_cast<int>(errorType));
    delete currentMeterageMessage;
    delete currentReceivedMessage;
}

void unitTest::testNoScheduleError()
{
    using namespace Enumerations;
    CommandCenter commandCenter;

    uint64_t deviceId = 41244;
    std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}};

    sendOneErrorMessage(commandCenter, deviceId, {0, 1}, {0, 1}, ErrorType::noSchedule);
    sendOneErrorMessage(commandCenter, deviceId, {1, 2}, {1, 43}, ErrorType::noSchedule);
    sendOneErrorMessage(commandCenter, deviceId, {2, 55}, {2, 55}, ErrorType::noSchedule);
    sendOneErrorMessage(commandCenter, deviceId, {3, 53}, {3, 15}, ErrorType::noSchedule);
    sendOneErrorMessage(commandCenter, deviceId, {4, 12}, {4, 10}, ErrorType::noSchedule);
    sendOneErrorMessage(commandCenter, deviceId, {5, 53}, {5, 15}, ErrorType::noSchedule);
    sendOneErrorMessage(commandCenter, deviceId, {6, 34}, {6, 10}, ErrorType::noSchedule);
}

void unitTest::testNoTimeStampError()
{
    using namespace Enumerations;
    CommandCenter commandCenter;

    uint64_t deviceId = 10213;
    std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}};
    DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

    commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);
    sendOneErrorMessage(commandCenter, deviceId, {0, 1}, {213, 1}, ErrorType::noTimestamp);
    sendOneErrorMessage(commandCenter, deviceId, {1, 2}, {23523, 43}, ErrorType::noTimestamp);
    sendOneErrorMessage(commandCenter, deviceId, {2, 55}, {5235, 55}, ErrorType::noTimestamp);
    sendOneErrorMessage(commandCenter, deviceId, {3, 53}, {352, 15}, ErrorType::noTimestamp);
    sendOneErrorMessage(commandCenter, deviceId, {4, 12}, {5232, 10}, ErrorType::noTimestamp);
    sendOneErrorMessage(commandCenter, deviceId, {5, 53}, {153, 15}, ErrorType::noTimestamp);
    sendOneErrorMessage(commandCenter, deviceId, {6, 34}, {592348, 10}, ErrorType::noTimestamp);

    commandCenter.unsetDeviceWorkSchedule(deviceId);

    delete correctDeviceWorkSchedule;
}

void unitTest::testObsoleteError()
{
    using namespace Enumerations;
    CommandCenter commandCenter;

    uint64_t deviceId = 10213;
    std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}, {7, 41}};
    DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

    commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

    sendOneCommandMessage(commandCenter, deviceId, {7, 41}, {7, 56});
    sendOneErrorMessage(commandCenter, deviceId, {1, 2}, {1, 43}, ErrorType::obsolete);
    sendOneErrorMessage(commandCenter, deviceId, {2, 55}, {2, 55}, ErrorType::obsolete);
    sendOneErrorMessage(commandCenter, deviceId, {3, 53}, {3, 15}, ErrorType::obsolete);
    sendOneErrorMessage(commandCenter, deviceId, {4, 12}, {4, 10}, ErrorType::obsolete);
    sendOneErrorMessage(commandCenter, deviceId, {5, 53}, {5, 15}, ErrorType::obsolete);
    sendOneErrorMessage(commandCenter, deviceId, {6, 34}, {6, 10}, ErrorType::obsolete);

    commandCenter.unsetDeviceWorkSchedule(deviceId);

    delete correctDeviceWorkSchedule;
}

void unitTest::testErrorMessage()
{
    testNoScheduleError();
    testNoTimeStampError();
    testObsoleteError();
}

void sendAllIncorrectFormatMessages(CommandCenter &commandCenter, uint64_t deviceId)
{
    using namespace Enumerations;
    AbstractMessage *currentIncorrectFormatMessage;

    currentIncorrectFormatMessage = new CommandMessage(0.124);
    try {
        commandCenter.receiveAndSendMessage(deviceId, currentIncorrectFormatMessage);
    } catch (const std::invalid_argument& ex) {
        ASSERT_EQUAL(std::string(ex.what()), "receiveAndSentMessage has invalid argument");
    }
    delete currentIncorrectFormatMessage;


    currentIncorrectFormatMessage = new ErrorMessage(ErrorType::noSchedule);

    try {
        commandCenter.receiveAndSendMessage(deviceId, currentIncorrectFormatMessage);
    } catch (const std::invalid_argument& ex) {
        ASSERT_EQUAL(std::string(ex.what()), "receiveAndSentMessage has invalid argument");
    }
    delete currentIncorrectFormatMessage;

    currentIncorrectFormatMessage = new ErrorMessage(ErrorType::noTimestamp);

    try {
        commandCenter.receiveAndSendMessage(deviceId, currentIncorrectFormatMessage);
    } catch (const std::invalid_argument& ex) {
        ASSERT_EQUAL(std::string(ex.what()), "receiveAndSentMessage has invalid argument");
    }
    delete currentIncorrectFormatMessage;

    currentIncorrectFormatMessage = new ErrorMessage(ErrorType::obsolete);

    try {
        commandCenter.receiveAndSendMessage(deviceId, currentIncorrectFormatMessage);
    } catch (const std::invalid_argument& ex) {
        ASSERT_EQUAL(std::string(ex.what()), "receiveAndSentMessage has invalid argument");
    }
    delete currentIncorrectFormatMessage;
}

 void unitTest::testIncorrectFormatMessage()
 {
     using namespace Enumerations;
     CommandCenter commandCenter;

     uint64_t deviceId = 10213;
     std::vector<Phase> correctSchedule = {{0, 1}, {1, 2}, {2, 55}, {3, 53}, {4, 12}, {5, 53}, {6, 34}, {7, 41}};
     DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

     commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

     sendAllIncorrectFormatMessages(commandCenter, deviceId);

     commandCenter.unsetDeviceWorkSchedule(deviceId);

     delete correctDeviceWorkSchedule;
 }


void unitTest::testCommandCenterReceiveAndSendMessage()
{
    testCommandtMessage();
    testErrorMessage();
    testIncorrectFormatMessage();
}


