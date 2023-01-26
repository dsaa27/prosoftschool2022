#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Mirror.h"

std::string Mirror::encode(std::string message) const
{
    std::ostringstream os;
    std::istringstream is(message);
    std::string input;
    while (!is.eof())
    {
        is >> input;
        reverse(input.begin(), input.end());
        os << input;
        if (!is.eof())
            os << ' ';
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

