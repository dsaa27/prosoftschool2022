#include "ROT3.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

std::string ROT3::encode(std::string message) const
    {
        std::ostringstream os;
        std::istringstream is(message);
        std::string input;
        while (!is.eof())
        {
            is >> input;
            uint64_t number = std::stoull(input);
            if (number > UINT64_MAX - 3)
                number = UINT64_MAX - number + 2;
            else
                number += 3;
            os << number;
            if (!is.eof())
                os << ' ';
        }
        std::string res = os.str();
        return res;
    }

std::string ROT3::decode(std::string message) const
    {
        std::ostringstream os;
        std::istringstream is(message);
        std::string input;
        while (!is.eof())
        {
            is >> input;
            uint64_t number = std::stoull(input);
            if (number < 3)
                number = UINT64_MAX - 2 + number;
            else number -= 3;
            os << number;
            if (!is.eof())
                os << ' ';
        }
        std::string res = os.str();
        return res;
    }

std::string ROT3::getName() const {
    return "ROT3";
}





