#include "rot4.h"

std::string Rot4::encode (std::string message)
{
    std::string encodedMessage;
    for (char c : message)
    {
        encodedMessage.push_back(c + 4);
    }
    return encodedMessage;

}

std::string Rot4::decode (std::string message)
{
    std::string decodedMessage;
    for (char c : message)
    {
        decodedMessage.push_back(c - 4);
    }
    return decodedMessage;

}

std::string Rot4::name ()
{
    return m_name;
}
