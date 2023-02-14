#include "messageserializer.h"
#include <iostream>

#include <sstream>
#include <cstring>
#include <vector>

std::string MessageSerializer::serialize(const MessageDto& messageDto) const
{
    std::ostringstream ostrstream;
    ostrstream << messageDto.messageType << " ";
    switch(messageDto.messageType)
    {
        case MessageType::Command:
            ostrstream << messageDto.parameterTuning;
            break;
        case MessageType::Error:
            ostrstream << messageDto.errorType;
            break;
        case MessageType::Meterage:
            ostrstream << messageDto.meterage.timeStamp << " ";
            ostrstream << static_cast<uint64_t>(messageDto.meterage.value);
            break;
        default:
            std::cerr << "Unexpected message type: " << messageDto.messageType << std::endl;
            break;
    }
    return ostrstream.str();
}

MessageDto MessageSerializer::deserialize(const std::string& message) const
{
    MessageDto messageDto;
    std::istringstream istrstream(message);
    std::string strinput;


    istrstream >> strinput;
    uint64_t messageType = std::stoull(strinput);
    messageDto.messageType = static_cast<MessageType>(messageType);

    istrstream >> strinput;

    uint64_t errorType;

    switch(messageDto.messageType)
    {
        case MessageType::Command:
            messageDto.parameterTuning = std::stoll(strinput);
            break;
        case MessageType::Error:
            errorType = std::stoull(strinput);
            messageDto.errorType = static_cast<ErrorType>(errorType);
            break;
        case MessageType::Meterage:
            messageDto.meterage.timeStamp = std::stoull(strinput);
            istrstream >> strinput;
            messageDto.meterage.value = std::stoul(strinput);
            break;
        default:
            std::cerr << "Unexpected message type: " << messageDto.messageType << std::endl;
            break;
    }

    return messageDto;




    /*
    std::string input;
    std::istringstream is(message);
    is >> input;
    uint64_t type = std::stoull(input);
    MessageStruct result;
    switch(type)
    {
        case messageType::Command:
            result.type = messageType::Command;
            is >> input;
            result.valueToCorrect = std::stoll(input);
            break;
        case messageType::Meterage:
            result.type = messageType::Meterage;
            is >> input;
            result.phase.value =  std::stoul(input);
            is >> input;
            result.phase.timeStamp = std::stoull(input);
            break;
        case messageType::Error:
            result.type = messageType::Error;
            is >> input;
            result.errorCode = std::stoull(input);
            break;
        default:
            break;
    }
    return result;
      */

}
