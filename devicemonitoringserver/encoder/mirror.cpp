#include "mirror.h"

std::string Mirror::encode(std::string message)
{
    std::string encodedMessage;
    for (int i = message.size() - 1; i >= 0 ; i--)
    {
        encodedMessage.push_back(message[i]);
    }
    return encodedMessage;
}

std::string Mirror::decode(std::string message)
{
    return encode(message);
}

std::string Mirror::name()
{
    return m_name;;
}

