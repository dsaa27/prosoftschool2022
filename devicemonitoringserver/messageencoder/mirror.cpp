#include "mirror.h"
#include <algorithm>

Mirror::Mirror() :
    m_name("Mirror")
{}

std::string Mirror::encode(const std::string& message) const
{
    std::string encoded = message;
    std::reverse(encoded.begin(), encoded.end());
    return encoded;
}

std::string Mirror::decode(const std::string& message) const
{
    return encode(message);
}

std::string Mirror::getName() const
{
    return m_name;
}
