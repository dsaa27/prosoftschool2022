#include "messageserializer.h"

std::string MessageSerializer::serializeMessage (const AbstractMessage& other)
{
    std::string stringAsMessage = other.convert2string();
    return stringAsMessage;
}

AbstractMessage* MessageSerializer::deserializeMessage (const std::string& messageAsString)
{
    using namespace Enumerations;
    std::istringstream istream(messageAsString);
    MessageType messageType;
    int currentInt;
    istream >> currentInt;
    messageType = static_cast<MessageType>(currentInt);
    if (messageType == MessageType::command) {
        double correction;
        istream >> correction;
        return dynamic_cast<AbstractMessage*>(new CommandMessage(correction));
    } else if (messageType == MessageType::error) {
        ErrorType errorType;
        istream >> currentInt;
        errorType = static_cast<ErrorType>(currentInt);
        return dynamic_cast<AbstractMessage*>(new ErrorMessage(errorType));
    } else {
        uint64_t timeStamp;
        int measureValue;
        istream >> timeStamp >> measureValue;
        return dynamic_cast<AbstractMessage*>(new MeterageMessage(timeStamp, static_cast<uint8_t>(measureValue)));
    }
}
