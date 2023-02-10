#include "MessageSerializator.h"
#include <iostream>

std::string MessageSerializator::serialize(MessageStruct message) {
    std::ostringstream os;
    switch (message.type)
    {
        case messageType::Command:
            os << messageType::Command << " ";
            os << message.valueToCorrect;
            break;
        case messageType::Error:
            os << messageType::Error << " ";
            os << static_cast<uint64_t>(message.errorCode);
            break;
        case messageType::Meterage:
            os << messageType::Meterage << " ";
            os << static_cast<uint64_t>(message.phase.value) << " ";
            os << message.phase.timeStamp;
            break;
        default:
            break;
    }
    return os.str();
}

MessageSerializator::MessageStruct MessageSerializator::deserialize(const std::string &message) {
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
}
