#include "Multiply41.h"
#include <string>

std::string Multiply41::encode(const std::string& message) const
{
    std::string encodedMessage;
    char symbol;
    for(int i = 0; i < message.size(); i++)
    {
        int16_t mul41 = message[i] * 41;
        char ost = mul41 % CHAR_MAX;
        char intPart = mul41 / CHAR_MAX;
        encodedMessage.push_back(intPart);
        encodedMessage.push_back(ost);
    }
    return encodedMessage;
}

std::string Multiply41::decode(const std::string& message) const
{
    std::string decodedMessage;
    char symbol;
    size_t messageSize = message.size();
    for(int i = 0; i < messageSize - 1; ++i)
    {
        symbol = (static_cast<int16_t>(message[i]) * CHAR_MAX + static_cast<int16_t>(message[i + 1])) / 41;
        decodedMessage.push_back(symbol);
        i++;
    }
    return decodedMessage;
}

std::string Multiply41::getName() const {
    return "Multiply41";
}
