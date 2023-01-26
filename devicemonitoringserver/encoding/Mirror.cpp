#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Mirror.h"

std::string Mirror::encode(std::string message) const
{
    std::ostringstream os;
    for (int i = 0 ; i < message.length(); i++)
    {
        if (std::isspace(message[i])) {
            os << message[i];
            continue;
        }
        else
        {
            std::string strToReverse;
            strToReverse += message[i];
            while (i < message.length() - 1 && !std::isspace(message[i + 1]))
            {
                strToReverse += message[i + 1];
                i++;
            }
            reverse(strToReverse.begin(), strToReverse.end());
            os << strToReverse;
        }
    }
    std::string res = os.str();
    return res;
}

std::string Mirror::decode(std::string message) const
{
    std:: string result = encode(message);
    return  result;
}

std::string Mirror::getName() const {
    return "Mirror";
}

