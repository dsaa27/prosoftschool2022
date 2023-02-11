#include "unittest.h"
#include "../clientservercomponents/messageserializer.h"
#include "../test_runner.h"

void unitTest::serialization::meterageMessage()
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

void unitTest::serialization::commandMessage()
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

void unitTest::serialization::errorMessage()
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
