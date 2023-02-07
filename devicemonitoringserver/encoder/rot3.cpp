#include "rot3.h"

std::string Rot3::encode(std::string message)
{
    std::string encodedMessage;
    for (char c : message)
    {
        encodedMessage.push_back(c + 3);
    }
    return encodedMessage;
}

std::string Rot3::decode(std::string message)
{
    std::string decodedMessage;
    for (char c : message)
    {
        decodedMessage.push_back(c - 3);
    }
    return decodedMessage;
}
std::string Rot3::name()
{
    return m_name;;
}
