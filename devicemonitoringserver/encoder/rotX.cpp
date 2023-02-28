#include "rotX.h"

RotX::RotX(unsigned int offset) : m_offset(offset)
{
    m_name += std::to_string(offset);
}

std::string RotX::encode (const std::string& message)
{
    std::string encodedMessage;
    for (const char& c : message)
    {
        encodedMessage.push_back(c + m_offset);
    }
    return encodedMessage;
}

std::string RotX::decode (const std::string& message)
{
    std::string decodedMessage;
    for (const char& c : message)
    {
        decodedMessage.push_back(c - m_offset);
    }
    return decodedMessage;
}

std::string RotX::name ()
{
    return m_name;
}
