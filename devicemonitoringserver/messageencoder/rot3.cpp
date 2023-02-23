#include "rot3.h"
#include <limits.h>

#define KEY 3

ROT3::ROT3() :
    m_name("ROT3")
{}

std::string ROT3::encode(const std::string& message) const
{
    std::string encoded;
    for(char symbol : message)
    {
        encoded += symbol <= CHAR_MAX - KEY ? symbol + KEY : CHAR_MIN + KEY - (CHAR_MAX - symbol) - 1;
    }
    return encoded;
}

std::string ROT3::decode(const std::string& message) const
{
    std::string decoded;
    for(char symbol : message)
    {
        decoded += symbol >= CHAR_MIN + KEY ? symbol - KEY : CHAR_MAX - KEY + (symbol - CHAR_MIN) + 1;
    }
    return decoded;
}

std::string ROT3::getName() const
{
    return m_name;
}
