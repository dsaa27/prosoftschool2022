#include "ROT3.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

std::string ROT3::encode(const std::string& message) const
    {
        std::ostringstream os;
        std::istringstream is(message);
        std::string input;
        while (!is.eof())
        {
            is >> input;
            int64_t number = std::stoll(input);
            number += 3;
            os << number;
            if (!is.eof())
                os << ' ';
        }
        return os.str();
    }

std::string ROT3::decode(const std::string& message) const
    {
        std::ostringstream os;
        std::istringstream is(message);
        std::string input;
        while (!is.eof())
        {
            is >> input;
            int64_t number = std::stoll(input);
            number -= 3;
            os << number;
            if (!is.eof())
                os << ' ';
        }
         return os.str();
    }

std::string ROT3::getName() const {
    return "ROT3";
}





