#include "multiply41.h"

#define MULT 41
#define DIV 128

Multiply41::Multiply41() :
    m_name("Multiply41")
{}

std::string Multiply41::encode(const std::string& message) const
{
    std::string encoded;
    int16_t value;
    for (int8_t i : message)
    {
        value = i * MULT;
        encoded += static_cast<char>(value / DIV);
        encoded += static_cast<char>(value % DIV);
    }
    return encoded;
}

std::string Multiply41::decode(const std::string& message) const
{
    std::string decoded;
    int length = message.size();
    int16_t value;
    for (int i = 0; i < length - 1; i += 2)
    {
        value = static_cast<int16_t>(message[i]) * DIV + static_cast<int16_t>(message[i + 1]);
        value /= MULT;
        decoded += static_cast<char>(value);
    }
    return decoded;
}

std::string Multiply41::getName() const
{
    return m_name;
}
