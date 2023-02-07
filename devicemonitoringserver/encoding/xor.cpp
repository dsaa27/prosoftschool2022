#include "Xor.h"

std::string Xor::encode(const std::string &message) const
{
    char key[4] = {'A', 'C', 'B', 'W'};
        std::string output;
        for (int i = 0; i < message.size(); i++)
            output += message[i] ^ key[i % (sizeof(key) / sizeof(char))];
        return output;
}

std::string Xor::decode(const std::string &message) const
{
    return encode(message);
}

std::string Xor::getName() const
{
    return "Xor";
}
