#include "MessageSerializator.h"
#include <iostream>
MessageSerializator::MessageSerializator() = default;
MessageSerializator::~MessageSerializator() = default;

std::string
MessageSerializator::serialize(messageType messType, uint64_t errType,
                               uint64_t timeStamp, uint64_t value) const{
    std::ostringstream os;
    std::string result = "";
    switch (messType)
    {
        case messageType::Command:
            result.push_back(char(messageType::Command));
            result.push_back(' ');
            if (value > 100 || value < 0)
                result.push_back(char(value));
            else return "";
            break;
        case messageType::Error:
            if (errType != -1)
                return "";
            result.push_back(char(messageType::Error));
            result.push_back(char(errType));
            break;
        case messageType::Meterage:
            os << messageType::Meterage;
            result += std::to_string(messageType::Meterage);
            result += " ";
            if (value > 100 || value < 0)
                return "";
            else
            {
                os << value;
                result += std::to_string(value);
            }
            result += " ";
            if (timeStamp != -1)
            {
                os << timeStamp;
                result += std::to_string(timeStamp);
            }
            else return "";
            break;
        default:
            break;
    }
    return os.str();
}

std::string MessageSerializator::deserialize(const std::string &message) const {
    std::istringstream os;
    std::string result = "";
    int type;
    os >> type;
    std::cout << type;
    os.clear();
    switch(type)
    {
        case messageType::Command:
            break;
        case messageType::Meterage:
            break;
        case messageType::Error:
            break;
        default:
            break;
    }
    //std::string els[3] = strtok(noDeserialized, " ");
    return result;
}
