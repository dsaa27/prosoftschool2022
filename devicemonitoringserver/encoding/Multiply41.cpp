#include "Multiply41.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

std::string Multiply41::encode(std::string message) const
{
    std::ostringstream os;
    std::istringstream is(message);
    std::string input;
    while (!is.eof())
    {
        is >> input;
        int64_t number = std::stoll(input);
        int64_t numMul41 = number * 41;
        os << numMul41;
        if (!is.eof())
            os << ' ';
    }
    std::string res = os.str();
    return res;
}

std::string Multiply41::decode(std::string message) const
{
    std::ostringstream os;
    std::istringstream is(message);
    std::string input;
    while (!is.eof())
    {
        is >> input;
        int64_t number = std::stoll(input);
        int64_t numDiv41 = number / 41;
        os << numDiv41;
        if (!is.eof())
            os << ' ';
    }
    std::string res = os.str();
    return res;
}

std::string Multiply41::getName() const {
    return "Multiply41";
}
