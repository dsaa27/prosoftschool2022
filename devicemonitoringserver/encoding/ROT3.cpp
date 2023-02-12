#include "ROT3.h"
#include <string>

std::string ROT3::encode(const std::string& message) const
{
    std::string encodedMessage;
    char symbol;
    size_t messageSize = message.size();
    for(int i = 0; i < messageSize; ++i)
    {
        symbol = message[i] < CHAR_MAX - 2 ? message[i] + 3 : CHAR_MIN + 2 - (CHAR_MAX - message[i]);
        encodedMessage.push_back(symbol);
    }
    return encodedMessage;
}

std::string ROT3::decode(const std::string& message) const
{
    std::string decodedMessage;
    char symbol;
    size_t messageSize = message.size();
    for(int i = 0; i < messageSize; ++i)
    {
        symbol = message[i] > CHAR_MIN - 2 ? message[i] - 3 : CHAR_MAX - 3 - (CHAR_MIN  - message[i]);
        decodedMessage.push_back(symbol);
    }
    return decodedMessage;
}

std::string ROT3::getName() const {
    return "ROT3";
}





