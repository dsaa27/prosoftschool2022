#include "multiply41.h"

std::string Multiply41::encode(std::string message)
{
    std::string encodedMessage;
    for (char c : message)
    {
        uint16_t duobleChar = c*41;
        char minorByte = duobleChar % 256;
        duobleChar /= 256;
        char majorByte = duobleChar % 256;
        encodedMessage.push_back(majorByte);
        encodedMessage.push_back(minorByte);
    }
    return encodedMessage;
}

std::string Multiply41::decode(std::string message)
{
    std::string decodeMessage;
    for (unsigned int i = 0; i < message.size(); i += 2)
    {
        uint8_t majorByte = static_cast<uint8_t>(message[i]);
        uint8_t minorByte = static_cast<uint8_t>(message [i + 1]);
        uint16_t duobleChar = majorByte*256 + minorByte;
        char c = duobleChar/41;
        decodeMessage.push_back(c);
    }
    return decodeMessage;
}

std::string Multiply41::name()
{
    return m_name;
}
