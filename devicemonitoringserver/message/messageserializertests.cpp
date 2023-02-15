#include "messageserializertests.h"
#include "test_runner.h"
#include "messageserializer.h"

void assertEquelMessage(const MessageDto& messageActual, const MessageDto& messageExpected)
{
    ASSERT_EQUAL(messageActual.messageType, messageExpected.messageType);
    ASSERT_EQUAL(messageActual.errorType, messageExpected.errorType);
    ASSERT_EQUAL(messageActual.parameterTuning, messageExpected.parameterTuning);
    ASSERT_EQUAL(messageActual.meterage.timeStamp, messageExpected.meterage.timeStamp);
    ASSERT_EQUAL(messageActual.meterage.value, messageExpected.meterage.value);
}

void runTestCase(const MessageSerializer& serializer, const MessageDto& messageDto, const std::string& strMesssage)
{
    std::string result = serializer.serialize(messageDto);
    ASSERT_EQUAL(result, strMesssage)

    MessageDto messageActual = serializer.deserialize(result);
    assertEquelMessage(messageActual, messageDto);
}

void messageSerializerTest()
{
    MessageSerializer serializer;

    MessageDto commandMessage;
    commandMessage.messageType = MessageType::Command;
    commandMessage.parameterTuning = -25;
    runTestCase(serializer, commandMessage, "1 -25");

    MessageDto errorMessage;
    errorMessage.messageType = MessageType::Error;
    errorMessage.errorType = ErrorType::NoTimestamp;
    runTestCase(serializer, errorMessage, "2 2");

    MessageDto meterageMessage;
    meterageMessage.messageType = MessageType::Meterage;
    meterageMessage.meterage = {3, 50};
    runTestCase(serializer, meterageMessage, "0 3 50");
}
