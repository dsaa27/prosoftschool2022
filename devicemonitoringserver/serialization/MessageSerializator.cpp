#include "MessageSerializator.h"
#include <iostream>



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
    std::istringstream os(message);
    uint64_t type;
    os >> type;
    MessageStruct result;
    switch(type)
    {
        case messageType::Command:
            result.type = messageType::Command;
            os >> result.valueToCorrect;
            break;
        case messageType::Meterage:
            result.type = messageType::Meterage;
            os >> result.phase.value;
            os >> result.phase.timeStamp ;
            break;
        case messageType::Error:
            result.type = messageType::Error;
            os >> result.errorCode;
            break;
        default:
            break;
    }
    return result;
}
