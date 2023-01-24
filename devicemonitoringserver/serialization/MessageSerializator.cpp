#include "MessageSerializator.h"
#include <iostream>
#include <vector>

MessageSerializator::MessageSerializator() = default;
MessageSerializator::~MessageSerializator() = default;

std::string
MessageSerializator::serialize(messageType messType, uint64_t errType,
                               uint64_t timeStamp, uint8_t value) {
    std::ostringstream os;
    switch (messType)
    {
        case messageType::Command:
            os << messageType::Command << " ";
            os << value;
            break;
        case messageType::Error:
            if (errType != -1)
                return "";
            os << messageType::Error << " ";
            os << errType;
            break;
        case messageType::Meterage:
            os << messageType::Meterage << " ";
            if (value > 100 || value < 0)
                return "";
            else
                os << value << " ";
            if (timeStamp != -1)
                os << timeStamp;
            else return "";
            break;
        default:
            break;
    }
    return os.str();
}

std::vector<uint64_t> MessageSerializator::deserialize(const std::string &message) {
    std::istringstream os(message);
    uint64_t type;
    os >> type;
    std::vector<uint64_t> res = {};
    res.push_back(type);
    switch(type)
    {
        case messageType::Command:
            uint8_t valueToCorrect;
            os >> valueToCorrect;
            res.push_back(valueToCorrect);
            break;
        case messageType::Meterage:
            uint8_t value;
            uint64_t timeStamp;
            os >> value;
            os >> timeStamp;
            res.push_back(value);
            res.push_back(timeStamp);
            break;
        case messageType::Error:
            uint64_t errType;
            os >> errType;
            res.push_back(errType);
            break;
        default:
            break;
    }

    return res;
}
