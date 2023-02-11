#include "unittest.h"
#include "../clientservercomponents/messageserializer.h"
#include "../test_runner.h"

void unitTest::deserialization::meterageMessage()
{
    std::vector<std::pair<uint64_t,int>>
            expectedPhaseVector = {{1, 5},
                                   {2, 100},
                                   {124124, 34},
                                   {35897320489273ULL, 0},
                                   {0, 0}};
       std::vector<std::pair<uint64_t, int>> phaseVector;
       MessageSerializer messageSerializer;
       AbstractMessage *currentDeserializedAbstractMessage;
       MeterageMessage *currentDeserializedMeterageMessage;

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("1 1 5");
       currentDeserializedMeterageMessage = dynamic_cast<MeterageMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       phaseVector.push_back({currentDeserializedMeterageMessage->timeStamp, currentDeserializedMeterageMessage->measureValue});

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("1 2 100");
       currentDeserializedMeterageMessage = dynamic_cast<MeterageMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       phaseVector.push_back({currentDeserializedMeterageMessage->timeStamp, currentDeserializedMeterageMessage->measureValue});

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("1 124124 34");
       currentDeserializedMeterageMessage = dynamic_cast<MeterageMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       phaseVector.push_back({currentDeserializedMeterageMessage->timeStamp, currentDeserializedMeterageMessage->measureValue});

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("1 35897320489273 0");
       currentDeserializedMeterageMessage = dynamic_cast<MeterageMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       phaseVector.push_back({currentDeserializedMeterageMessage->timeStamp, currentDeserializedMeterageMessage->measureValue});

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("1 0 0");
       currentDeserializedMeterageMessage = dynamic_cast<MeterageMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       phaseVector.push_back({currentDeserializedMeterageMessage->timeStamp, currentDeserializedMeterageMessage->measureValue});

       ASSERT_EQUAL(phaseVector, expectedPhaseVector);

       delete currentDeserializedAbstractMessage;
}

void unitTest::deserialization::commandMessage()
{
    MessageSerializer messageSerializer;
    AbstractMessage *currentDeserializedAbstractMessage;
    CommandMessage *currentDeserializedCommandMessage;

    const double epsilon = 1e-6;

    currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("2 0");
    currentDeserializedCommandMessage = dynamic_cast<CommandMessage*>(currentDeserializedAbstractMessage);
    ASSERT(currentDeserializedAbstractMessage);
    ASSERT(std::abs(currentDeserializedCommandMessage->correction - 0.0) < epsilon);

    currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("2 0.01");
    currentDeserializedCommandMessage = dynamic_cast<CommandMessage*>(currentDeserializedAbstractMessage);
    ASSERT(currentDeserializedAbstractMessage);
    ASSERT(std::abs(currentDeserializedCommandMessage->correction - 0.01) < epsilon);

    currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("2 0.333333");
    currentDeserializedCommandMessage = dynamic_cast<CommandMessage*>(currentDeserializedAbstractMessage);
    ASSERT(currentDeserializedAbstractMessage);
    ASSERT(std::abs(currentDeserializedCommandMessage->correction - 0.333333) < epsilon);

    currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("2 0.012987");
    currentDeserializedCommandMessage = dynamic_cast<CommandMessage*>(currentDeserializedAbstractMessage);
    ASSERT(currentDeserializedAbstractMessage);
    ASSERT(std::abs(currentDeserializedCommandMessage->correction - 0.012987) < epsilon);

    currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("2 -0.027027");
    currentDeserializedCommandMessage = dynamic_cast<CommandMessage*>(currentDeserializedAbstractMessage);
    ASSERT(currentDeserializedAbstractMessage);
    ASSERT(std::abs(currentDeserializedCommandMessage->correction - (-0.027027)) < epsilon);

    delete currentDeserializedAbstractMessage;
}

void unitTest::deserialization::errorMessage()
{
    std::vector<int> expectedErrorVector = {1, 2, 3};
       std::vector<int> errorVector;
       MessageSerializer messageSerializer;
       AbstractMessage *currentDeserializedAbstractMessage;
       ErrorMessage *currentDeserializedErrorMessage;

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("3 1");
       currentDeserializedErrorMessage = dynamic_cast<ErrorMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       errorVector.push_back(static_cast<int>(currentDeserializedErrorMessage->errorType));

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("3 2");
       currentDeserializedErrorMessage = dynamic_cast<ErrorMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       errorVector.push_back(static_cast<int>(currentDeserializedErrorMessage->errorType));

       currentDeserializedAbstractMessage = messageSerializer.deserializeMessage("3 3");
       currentDeserializedErrorMessage = dynamic_cast<ErrorMessage*>(currentDeserializedAbstractMessage);
       ASSERT(currentDeserializedAbstractMessage);
       errorVector.push_back(static_cast<int>(currentDeserializedErrorMessage->errorType));

       ASSERT_EQUAL(errorVector, expectedErrorVector);

       delete currentDeserializedAbstractMessage;
}

void unitTest::deserialization::catchInvalidArgumentException(
        std::string &receivedExceptionMessage, const std::string& wrongDeserializeMessage)
{
    try {
        MessageSerializer messageSerializer;
        messageSerializer.checkInvalidDeserializeMessageArgument(wrongDeserializeMessage);
        receivedExceptionMessage = "";
    } catch (std::exception const& ex) {
        receivedExceptionMessage = ex.what();
    }
}

void unitTest::deserialization::invalidArgument()
{
    std::vector<std::string> received;
    std::string receivedExceptionMessage;

    catchInvalidArgumentException(receivedExceptionMessage, "-1 2 3");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "1241 2 3");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "1  5  8");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "0 92 034 35");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "1");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "1 -1");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "1 -1 4");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "");

    catchInvalidArgumentException(receivedExceptionMessage, "1 24321");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "2 0.12411");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "");

    catchInvalidArgumentException(receivedExceptionMessage, "2 -0.12");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "");

    catchInvalidArgumentException(receivedExceptionMessage, "2 -124");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "3 1");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "");

    catchInvalidArgumentException(receivedExceptionMessage, "3 2");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "");

    catchInvalidArgumentException(receivedExceptionMessage, "3 24321");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");

    catchInvalidArgumentException(receivedExceptionMessage, "3 -1");
    received.push_back(receivedExceptionMessage);
    ASSERT_EQUAL(receivedExceptionMessage,  "Deserializer has invalid argument");
}
