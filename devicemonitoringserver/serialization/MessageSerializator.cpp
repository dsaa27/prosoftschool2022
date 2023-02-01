#include "MessageSerializator.h"
#include <iostream>

std::string MessageSerializator::serialize(messageType messType, uint8_t errorCode,
                               uint64_t timeStamp, uint8_t value, int64_t valueToCorrect) {
    std::ostringstream os;
    switch (messType)
    {
        case messageType::Command:
            os << messageType::Command << " ";
            os << int64_t(valueToCorrect);
            break;
        case messageType::Error:
            os << messageType::Error << " ";
            os << uint64_t(errorCode);
            break;
        case messageType::Meterage:
            os << messageType::Meterage << " ";
            os << uint64_t(value) << " ";
            os << timeStamp;
            break;
        default:
            break;
    }
    std::string result = os.str();
    return result;
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
