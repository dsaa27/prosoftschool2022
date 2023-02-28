#include "multiply41.h"

std::string Multiply41::encode(const std::string& message)
{
    std::string encodedMessage;
    for (const char& c : message)
    {
        uint16_t doubleChar = c * 41;
        const char minorByte = doubleChar % 256;
        doubleChar /= 256;
        const char majorByte = doubleChar % 256;
        encodedMessage.push_back(majorByte);
        encodedMessage.push_back(minorByte);
    }
    return encodedMessage;
}

std::string Multiply41::decode(const std::string& message)
{
    std::string decodeMessage;
    for (unsigned int i = 0; i < message.size(); i += 2)
    {
        const uint8_t majorByte = static_cast<uint8_t>(message[i]);
        const uint8_t minorByte = static_cast<uint8_t>(message [i + 1]);
        const uint16_t doubleChar = majorByte * 256 + minorByte;
        const char c = doubleChar/41;
        decodeMessage.push_back(c);
    }
    return decodeMessage;
}

std::string Multiply41::name()
{
    return m_name;
}
