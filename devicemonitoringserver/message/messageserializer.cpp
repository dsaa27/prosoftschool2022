#include "messageserializer.h"
#include <iostream>

#include <sstream>
#include <cstring>
#include <vector>

bool MessageSerializer::serialize(const MessageDto& messageDto, std::string& message) const
{
    std::ostringstream ostrstream;
    ostrstream << messageDto.messageType << " ";
    switch(messageDto.messageType)
    {
        case MessageType::eCommand:
            ostrstream << messageDto.parameterTuning;
            break;
        case MessageType::eError:
            ostrstream << messageDto.errorType;
            break;
        case MessageType::eMeterage:
            ostrstream << messageDto.meterage.timeStamp << " ";
            ostrstream << static_cast<uint64_t>(messageDto.meterage.value);
            break;
        default:
            return false;
    }
    message = ostrstream.str();
    return true;
}

bool MessageSerializer::deserialize(const std::string& message, MessageDto& messageDto) const
{
    messageDto = {};
    std::istringstream istrstream(message);
    std::string strinput;

    istrstream >> strinput;
    uint64_t messageType = std::stoull(strinput);
    messageDto.messageType = static_cast<MessageType>(messageType);

    istrstream >> strinput;

    uint64_t errorType;

    switch(messageDto.messageType)
    {
        case MessageType::eCommand:
            messageDto.parameterTuning = std::stoll(strinput);
            break;
        case MessageType::eError:
            errorType = std::stoull(strinput);
            messageDto.errorType = static_cast<ErrorType>(errorType);
            break;
        case MessageType::eMeterage:
            messageDto.meterage.timeStamp = std::stoull(strinput);
            istrstream >> strinput;
            messageDto.meterage.value = std::stoul(strinput);
            break;
        default:
            return false;
    }
    return true;
}
