#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Mirror.h"

std::string Mirror::encode(const std::string& message) const
{
    std::ostringstream os;
    std::istringstream is(message);
    std::string input;
    while (!is.eof())
    {
        is >> input;
        if (input.empty())
            continue;
        reverse(input.begin(), input.end());
        os << input;
        if (!is.eof())
            os << ' ';
    }
    return os.str();
}

std::string Mirror::decode(const std::string& message) const
{
    return  encode(message);
}

std::string Mirror::getName() const {
    return "Mirror";
}

