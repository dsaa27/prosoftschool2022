#include "messageSerializator.h"

std::string MessageSerializer::serializate(const MessageStruct& message)
{
    std::ostringstream serialMessage;
    serialMessage << message.messageType;
    serialMessage << ' ';
    if (message.messageType == METERAGE)
    {
        serialMessage << std::to_string(message.measurements.timeStamp);
        serialMessage << ' ';
        serialMessage << std::to_string(message.measurements.value);
    }

    if (message.messageType == COMMAND)
    {
        serialMessage << message.adjustment;
    }

    if (message.messageType == ERROR)
    {
        serialMessage << static_cast<int> (message.errorType);
    }

    return serialMessage.str();
};

MessageStruct MessageSerializer::deserializate(const std::string& serialMessage)
{
    MessageStruct message;
    std::istringstream iStr(serialMessage);
    std::string buffer;
    iStr >> buffer;
    message.messageType = stoi(buffer);

    switch (message.messageType) {
    case METERAGE:
        {
        iStr >> buffer;
        message.measurements.timeStamp = std::stoll(buffer);
        iStr >> buffer;
        message.measurements.value = std::stoi(buffer);
        break;
        }
    case COMMAND:
        iStr >> buffer;
        message.adjustment = std::stoll(buffer);
        break;
    case ERROR:
        iStr >> buffer;
        message.errorType = std::stoll(buffer);
        break;
    }
    return message;
};
