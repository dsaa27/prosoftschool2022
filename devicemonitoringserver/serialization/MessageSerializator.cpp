#include "MessageSerializator.h"
#include <iostream>
#include <vector>


MessageSerializator::MessageSerializator() = default;
MessageSerializator::~MessageSerializator() = default;

std::string MessageSerializator::serialize(messageType messType, uint8_t errorCode,
                               uint64_t timeStamp, uint8_t value) {
    std::ostringstream os;
    switch (messType)
    {
        case messageType::Command:
            os << messageType::Command << " ";
            os << value << " ";
            break;
        case messageType::Error:
            os << messageType::Error << " ";
            os << errorCode;
            break;
        case messageType::Meterage:
            os << messageType::Meterage << " ";
            os << value << " ";
            os << timeStamp;
            break;
        default:
            break;
    }
    std::string result = os.str();
    return result;
}

MessageSerializator::MessageStruct MessageSerializator::deserialize(const std::string &message) {
    std::istringstream os(message);
    uint64_t type;
    os >> type;
    MessageStruct result;
    switch(type)
    {
        case messageType::Command:
            result.type = messageType::Command;
            uint8_t valueToCorrect;
            os >> valueToCorrect;
            result.valueToCorrect = valueToCorrect;
            break;
        case messageType::Meterage:
            result.type = messageType::Meterage;
            uint8_t value;
            uint64_t timeStamp;

            os >> value;
            os >> timeStamp;

            result.phase.value = value;
            result.phase.timeStamp = timeStamp;
            break;
        case messageType::Error:
            result.type = messageType::Error;
            uint64_t errorCode;
            os >> errorCode;
            result.errorCode = errorCode;
            break;
        default:
            break;
    }
    return result;
}
