#include "MessageSerializator.h"
#include <iostream>

std::string MessageSerializator::serialize(MessageStruct message) {
    std::ostringstream os;
    switch (message.type)
    {
        case messageType::Command:
            os << messageType::Command << " ";
            os << int64_t(message.valueToCorrect);
            break;
        case messageType::Error:
            os << messageType::Error << " ";
            os << uint64_t(message.errorCode);
            break;
        case messageType::Meterage:
            os << messageType::Meterage << " ";
            os << uint64_t(message.phase.value) << " ";
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

    uint8_t value;
    int64_t valueToCorrect;
    uint64_t timeStamp;
    uint64_t errorCode;
    MessageStruct result;
    switch(type)
    {
        case messageType::Command:
            result.type = messageType::Command;
            is >> input;
            valueToCorrect = std::stoll(input);
            result.valueToCorrect = valueToCorrect;
            break;
        case messageType::Meterage:
            result.type = messageType::Meterage;
            is >> input;
            value = std::stoul(input);
            result.phase.value = value;
            is >> input;
            timeStamp = std::stoull(input);
            result.phase.timeStamp = timeStamp;
            break;
        case messageType::Error:
            result.type = messageType::Error;
            is >> input;
            errorCode = std::stoull(input);
            result.errorCode = errorCode;
            break;
        default:
            break;
    }
    return result;
}
