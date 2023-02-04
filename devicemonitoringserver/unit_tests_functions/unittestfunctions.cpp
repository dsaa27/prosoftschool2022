#include "../test_runner.h"
#include "../clientservercomponents/abstractmessage.h"
#include "../clientservercomponents/messageserializer.h"

void testMeasureMessageSerialization(uint64_t timeStamp, uint8_t measureValue, const std::string& expectSerializedMessage)
{
    MessageSerializer messageSerializer;

    MeterageMessage newMeterageMessage(timeStamp, measureValue);

    ASSERT_EQUAL(expectSerializedMessage, messageSerializer.serializeMessage(newMeterageMessage));
}

void testCommandMessageSerialization(double correction, const std::string& expectSerializedMessage)
{
    MessageSerializer messageSerializer;

    CommandMessage newCommandMessage(correction);

    ASSERT_EQUAL(expectSerializedMessage, messageSerializer.serializeMessage(newCommandMessage));
}

void testErrorMessageSerialization(Enumerations::ErrorType errorType, const std::string& expectSerializedMessage)
{
    MessageSerializer messageSerializer;

    ErrorMessage newErrorMessage(errorType);

    ASSERT_EQUAL(expectSerializedMessage, messageSerializer.serializeMessage(newErrorMessage));
}

void testMeasureMessageDeserialization(const std::string& messageAsString, uint64_t timeStamp, uint8_t measureValue)
{
    MessageSerializer messageSerializer;

    AbstractMessage *deserializedMessage = messageSerializer.deserializeMessage(messageAsString);

    MeterageMessage *deserializedMeterageMessage = dynamic_cast<MeterageMessage*>(deserializedMessage);

    ASSERT(deserializedMeterageMessage);
    ASSERT_EQUAL(deserializedMeterageMessage->measureValue, measureValue);
    ASSERT_EQUAL(deserializedMeterageMessage->timeStamp, timeStamp);
}

void testCommandMessageDeserialization(const std::string& messageAsString, double correction)
{
    MessageSerializer messageSerializer;

    AbstractMessage *deserializedMessage = messageSerializer.deserializeMessage(messageAsString);

    CommandMessage *deserializedCommandMessage = dynamic_cast<CommandMessage*>(deserializedMessage);

    double epsilon = 1e-6;

    ASSERT(deserializedCommandMessage);
    ASSERT(std::abs(deserializedCommandMessage->correction - correction) <= epsilon);
}

void testErrorMessageDeserialization(const std::string& messageAsString, Enumerations::ErrorType errorType)
{
    MessageSerializer messageSerializer;

    AbstractMessage *deserializedMessage = messageSerializer.deserializeMessage(messageAsString);

    ErrorMessage *deserializedErrorMessage = dynamic_cast<ErrorMessage*>(deserializedMessage);

    ASSERT(deserializedErrorMessage);
    ASSERT_EQUAL(static_cast<int>(deserializedErrorMessage->errorType), static_cast<int>(errorType));
}

void testCheckInvalidDeserializeMessageArgument(const std::string &messageAsString, const std::string &exceptionMessage)
{
    try {
        MessageSerializer messageSerializer;
        messageSerializer.checkInvalidDeserializeMessageArgument(messageAsString);
        ASSERT(exceptionMessage == "");
    } catch (std::exception const& ex) {
        ASSERT_EQUAL(ex.what(), exceptionMessage);
    }
}


