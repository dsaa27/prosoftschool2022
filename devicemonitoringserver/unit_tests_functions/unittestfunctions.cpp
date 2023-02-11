#include "../test_runner.h"
#include "../clientservercomponents/abstractmessage.h"
#include "../clientservercomponents/messageserializer.h"
#include "unittestfunctions.h"
#include "../clientservercomponents/commandcenter.h"

#include <random>

void testMeasureMessageSerialization()
{
    std::vector<std::string> expectedSerializedVector = {"1 1 5",
                                                         "1 2 100",
                                                         "1 124124 34",
                                                         "1 35897320489273 0",
                                                         "1 0 0"};
    std::vector<std::string> serializedVector;
    MessageSerializer messageSerializer;
    MeterageMessage currentMeterageMessage;

    currentMeterageMessage = {1, 5};
    serializedVector.push_back(messageSerializer.serializeMessage(currentMeterageMessage));
    currentMeterageMessage = {2, 100};
    serializedVector.push_back(messageSerializer.serializeMessage(currentMeterageMessage));
    currentMeterageMessage = {124124, 34};
    serializedVector.push_back(messageSerializer.serializeMessage(currentMeterageMessage));
    currentMeterageMessage = {35897320489273ULL,0};
    serializedVector.push_back(messageSerializer.serializeMessage(currentMeterageMessage));
    currentMeterageMessage = {0, 0};
    serializedVector.push_back(messageSerializer.serializeMessage(currentMeterageMessage));

    ASSERT_EQUAL(serializedVector, expectedSerializedVector);
}

void testCommandMessageSerialization()
{
    std::vector<std::string> expectedSerializedVector = {"2 0",
                                                         "2 0.01",
                                                         "2 0.333333",
                                                         "2 0.010101",
                                                         "2 0.012987",
                                                         "2 -0.027027",
                                                         "2 -0.0588235"};
    std::vector<std::string> serializedVector;
    MessageSerializer messageSerializer;
    CommandMessage currentCommandMessage;
    std::string currentSerializedMessage;

    currentCommandMessage = {0.0};
    currentSerializedMessage = messageSerializer.serializeMessage(currentCommandMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentCommandMessage = {0.01};
    currentSerializedMessage = messageSerializer.serializeMessage(currentCommandMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentCommandMessage = {1.0 / 3};
    currentSerializedMessage = messageSerializer.serializeMessage(currentCommandMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentCommandMessage = {1.0 / 99};
    currentSerializedMessage = messageSerializer.serializeMessage(currentCommandMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentCommandMessage = {1.0 / 77};
    currentSerializedMessage = messageSerializer.serializeMessage(currentCommandMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentCommandMessage = {1.0 / -37};
    currentSerializedMessage = messageSerializer.serializeMessage(currentCommandMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentCommandMessage = {1.0 / -17};
    currentSerializedMessage = messageSerializer.serializeMessage(currentCommandMessage);
    serializedVector.push_back(currentSerializedMessage);

    ASSERT_EQUAL(serializedVector, expectedSerializedVector);
}

void testErrorMessageSerialization()
{
    using namespace Enumerations;
    std::vector<std::string> expectedSerializedVector = {"3 1",
                                                         "3 2",
                                                         "3 3"};
    std::vector<std::string> serializedVector;
    MessageSerializer messageSerializer;
    ErrorMessage currentErrorMessage;
    std::string currentSerializedMessage;

    currentErrorMessage = {ErrorType::noSchedule};
    currentSerializedMessage = messageSerializer.serializeMessage(currentErrorMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentErrorMessage = {ErrorType::noTimestamp};
    currentSerializedMessage = messageSerializer.serializeMessage(currentErrorMessage);
    serializedVector.push_back(currentSerializedMessage);
    currentErrorMessage = {ErrorType::obsolete};
    currentSerializedMessage = messageSerializer.serializeMessage(currentErrorMessage);
    serializedVector.push_back(currentSerializedMessage);

    ASSERT_EQUAL(serializedVector, expectedSerializedVector);
}

void testMeasureMessageDeserialization
    (const std::string messageAsString, uint64_t timeStamp, uint8_t measureValue)
{
    MessageSerializer messageSerializer;

    AbstractMessage *deserializedMessage = messageSerializer.deserializeMessage(messageAsString);

    MeterageMessage *deserializedMeterageMessage = dynamic_cast<MeterageMessage*>(deserializedMessage);

    ASSERT(deserializedMeterageMessage);
    ASSERT_EQUAL(deserializedMeterageMessage->measureValue, measureValue);
    ASSERT_EQUAL(deserializedMeterageMessage->timeStamp, timeStamp);
}

void testCommandMessageDeserialization
    (const std::string messageAsString, double correction)
{
    MessageSerializer messageSerializer;

    AbstractMessage *deserializedMessage = messageSerializer.deserializeMessage(messageAsString);

    CommandMessage *deserializedCommandMessage = dynamic_cast<CommandMessage*>(deserializedMessage);

    double epsilon = 1e-6;

    ASSERT(deserializedCommandMessage);
    ASSERT(std::abs(deserializedCommandMessage->correction - correction) <= epsilon);
}

void testErrorMessageDeserialization
    (const std::string messageAsString, Enumerations::ErrorType errorType)
{
    MessageSerializer messageSerializer;

    AbstractMessage *deserializedMessage = messageSerializer.deserializeMessage(messageAsString);

    ErrorMessage *deserializedErrorMessage = dynamic_cast<ErrorMessage*>(deserializedMessage);

    ASSERT(deserializedErrorMessage);
    ASSERT_EQUAL(static_cast<int>(deserializedErrorMessage->errorType), static_cast<int>(errorType));
}

void unitTestFunctions::testCheckInvalidDeserializeMessageArgument
    (const std::string messageAsString, const std::string exceptionMessage)
{
    try {
        MessageSerializer messageSerializer;
        messageSerializer.checkInvalidDeserializeMessageArgument(messageAsString);
        ASSERT_EQUAL(exceptionMessage, "");
    } catch (std::exception const& ex) {
        ASSERT_EQUAL(ex.what(), exceptionMessage);
    }
}

void unitTestFunctions::testMessageSerialization()
{
    testMeasureMessageSerialization();
    testCommandMessageSerialization();
    testErrorMessageSerialization();
}

void unitTestFunctions::testMessageDeserialization()
{
    using namespace Enumerations;

    testMeasureMessageDeserialization("1 1 5", 1, 5);
    testMeasureMessageDeserialization("1 2 100", 2, 100);
    testMeasureMessageDeserialization("1 124124 34", 124124, 34);
    testMeasureMessageDeserialization("1 35897320489273 0", 35897320489273ULL, 0);
    testMeasureMessageDeserialization("1 0 0", 0, 0);

    testCommandMessageDeserialization("2 0", 0.0);
    testCommandMessageDeserialization("2 0.01", 0.01);
    testCommandMessageDeserialization("2 0.333333", 1.0 / 3);
    testCommandMessageDeserialization("2 0.010101", 1.0 / 99);
    testCommandMessageDeserialization("2 0.012987", 1.0 / 77);

    testErrorMessageDeserialization("3 1", ErrorType::noSchedule);
    testErrorMessageDeserialization("3 2", ErrorType::noTimestamp);
    testErrorMessageDeserialization("3 3", ErrorType::obsolete);

    testCheckInvalidDeserializeMessageArgument("-1 2 3", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1241 2 3", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1241 2 3", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1  5  8", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("0 92 034 35", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1 92 34 35", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1 -1", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1 -1 4", "");
    testCheckInvalidDeserializeMessageArgument("1 24321", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("2 0.12411", "");
    testCheckInvalidDeserializeMessageArgument("2 -0.12", "");
    testCheckInvalidDeserializeMessageArgument("2 -124", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("3 1", "");
    testCheckInvalidDeserializeMessageArgument("3 2", "");
    testCheckInvalidDeserializeMessageArgument("3 24321", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("3 -1", "Deserializer has invalid argument");
}

DeviceWorkSchedule* unitTestFunctions::createRandomDeviceWorkSchedule()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<uint64_t> uint64_t_distribution;
    std::uniform_int_distribution<uint8_t> uint8_t_distribution(0, 100);

    uint64_t deviceId = uint64_t_distribution(generator);
    size_t size_of_schedule = uint8_t_distribution(generator);

    std::vector<Phase> schedule(size_of_schedule);


    uint64_t currentTimeStamp;
    uint8_t currentValue;
    for (size_t i = 0; i < size_of_schedule; i++) {
        //currentTimeStamp = uint64_t_distribution(generator);
        currentValue = uint8_t_distribution(generator);
        schedule[i] = {i, currentValue};
    }

    return new DeviceWorkSchedule(schedule, deviceId);
}

std::vector<uint8_t> unitTestFunctions::createRandomMeterageVector(size_t vectorSize)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<uint8_t> uint8_t_distribution(0, 100);

    std::vector<uint8_t> meterageVector(vectorSize);

    for(int i = 0; i < vectorSize; i++)
        meterageVector[i] = uint8_t_distribution(generator);

    return meterageVector;
}

void unitTestFunctions::testCommandCenterSetUnsetDeviceWorkSchedule()
{
    CommandCenter commandCenter;

    DeviceWorkSchedule *randomDeviceWorkSchedule1 = unitTestFunctions::createRandomDeviceWorkSchedule();
    uint64_t randomDeviceWorkSchedule1Id = randomDeviceWorkSchedule1->deviceId;

    DeviceWorkSchedule *randomDeviceWorkSchedule2 = unitTestFunctions::createRandomDeviceWorkSchedule();
    uint64_t randomDeviceWorkSchedule2Id = randomDeviceWorkSchedule2->deviceId;

    commandCenter.setDeviceWorkSchedule(randomDeviceWorkSchedule1);
    ASSERT_EQUAL(randomDeviceWorkSchedule1, commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule1Id));
    commandCenter.unsetDeviceWorkSchedule(randomDeviceWorkSchedule1Id);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule1Id), nullptr);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id), nullptr);
    commandCenter.unsetDeviceWorkSchedule(randomDeviceWorkSchedule2Id);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id), nullptr);
    commandCenter.setDeviceWorkSchedule(randomDeviceWorkSchedule2);
    ASSERT_EQUAL(randomDeviceWorkSchedule2, commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id));
    commandCenter.unsetDeviceWorkSchedule(randomDeviceWorkSchedule2Id);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id), nullptr);

    delete randomDeviceWorkSchedule1;
    delete randomDeviceWorkSchedule2;
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


void unitTestFunctions::testCommandtMessage()
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

void unitTestFunctions::testNoScheduleError()
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

void unitTestFunctions::testNoTimeStampError()
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

void unitTestFunctions::testObsoleteError()
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

void unitTestFunctions::testErrorMessage()
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

 void unitTestFunctions::testIncorrectFormatMessage()
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


void unitTestFunctions::testCommandCenterReceiveAndSendMessage()
{
    testCommandtMessage();
    testErrorMessage();
    testIncorrectFormatMessage();
}

double calculateStandardDeviation(double inaccuracy)
{
    static std::vector<double> allInaccuracies;

    allInaccuracies.push_back(inaccuracy);


    double average = 0;
    for (auto now : allInaccuracies) {
        average += now;
    }
    average /= allInaccuracies.size();

    double sumOfDeviationSquares= 0;

    for (auto now : allInaccuracies) {
        sumOfDeviationSquares += ((average - now) * (average - now));
    }

    return sqrt(sumOfDeviationSquares/allInaccuracies.size());
}

void unitTestFunctions::testStandardDeviationCalculation()
{
    CommandCenter commandCenter;

     uint64_t deviceId = 10213;
     std::vector<Phase> correctSchedule = {{0, 14}, {10, 23}, {20, 5}, {30, 3}, {40, 99}, {55, 38}, {61, 34}};
     DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctSchedule, deviceId);

     commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

     const double epsilon = 1e-4;

     sendOneCommandMessage(commandCenter, deviceId, {0, 14}, {0, 1});
     ASSERT((calculateStandardDeviation(1 - 14) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

     sendOneCommandMessage(commandCenter, deviceId, {10, 23}, {10, 43});
     ASSERT((calculateStandardDeviation(43 - 23) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

     sendOneCommandMessage(commandCenter, deviceId, {20, 5}, {20, 55});
     ASSERT((calculateStandardDeviation(55 - 5) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

     sendOneCommandMessage(commandCenter, deviceId, {30, 3}, {30, 15});
     ASSERT((calculateStandardDeviation(15 - 3) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

     sendOneCommandMessage(commandCenter, deviceId, {40, 99}, {40, 10});
     ASSERT((calculateStandardDeviation(10 - 99) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

     sendOneCommandMessage(commandCenter, deviceId, {55, 38}, {55, 38});
     ASSERT((calculateStandardDeviation(38 - 38) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

     sendOneCommandMessage(commandCenter, deviceId, {61, 34}, {61, 10});
     ASSERT((calculateStandardDeviation(10 - 34) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

     commandCenter.unsetDeviceWorkSchedule(deviceId);

     delete correctDeviceWorkSchedule;
}

