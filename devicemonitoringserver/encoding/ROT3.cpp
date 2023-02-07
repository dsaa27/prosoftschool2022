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
            if (input.empty())
                continue;
            if (input[0] == '-')
            {
                int64_t number = std::stoll(input);
                number = number < INT64_MAX - 3 ? number + 3 : INT64_MIN + INT64_MAX - number;
                os << number;
            }
            else
            {
                uint64_t number = std::stoull(input);
                number = number < UINT64_MAX - 3 ? number + 3 : UINT64_MAX - number;
                os << number;
            }
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
            if (input.empty())
                continue;
            if (input[0] == '-')
            {
                int64_t number = std::stoll(input);
                number -= 3;
                os << number;
            }
            else
            {
                //Пыталась переделать шифрование, но все равно не знаю как быть с границами,
                //если при шифровании число было uint64, то чтобы прибавить 3, число сделаем 0.
                //Как отличить это от случая когда былo число -3 и прибавив 3, тоже получили 0
                uint64_t number = std::stoull(input);
                if (number < 3)
                    os << int64_t(number) - 3;
                else
                {
                    number -= 3;
                    os << number;
                }
            }
            if (!is.eof())
                os << ' ';
        }
         return os.str();
    }

std::string ROT3::getName() const {
    return "ROT3";
}





