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
    std::string result;
    ASSERT(serializer.serialize(messageDto, result));
    ASSERT_EQUAL(result, strMesssage)

    MessageDto messageActual;
    ASSERT(serializer.deserialize(result, messageActual));
    assertEquelMessage(messageActual, messageDto);
}

void messageSerializerTest()
{
    MessageSerializer serializer;

    MessageDto commandMessage;
    commandMessage.messageType = MessageType::eCommand;
    commandMessage.parameterTuning = -25;
    runTestCase(serializer, commandMessage, "1 -25");

    MessageDto errorMessage;
    errorMessage.messageType = MessageType::eError;
    errorMessage.errorType = ErrorType::eNoTimestamp;
    runTestCase(serializer, errorMessage, "2 2");

    MessageDto meterageMessage;
    meterageMessage.messageType = MessageType::eMeterage;
    meterageMessage.meterage = {3, 50};
    runTestCase(serializer, meterageMessage, "0 3 50");

    MessageDto messageDto;
    ASSERT(!serializer.deserialize("3 5", messageDto));
}
