#include "ROT3.h"

ROT3::ROT3()
    {
        for (char i = 'a'; i < 'z'; i++)
        {
            alphabet.push_back(i);
        }

        for (int i = 0; i < 100; i++)
        {
            nums.push_back(i);
        }
    }

ROT3::~ROT3()
{

}

std::string ROT3::encode(std::string message) const
    {
        std:: string result = "";
        for (char i: message)
        {
            if (isalpha(i))
            {
                result += i <= 'z' - 3 ? alphabet[i - 97 + 3] : alphabet[2 - 'z' + i];
            }
            else if (std::isdigit(i))
            {
                result += i <= 6 ? nums[i + 3] : nums[2 - 9 + i];
            }
            else result += i;
        }
        return  result;
    }

std::string ROT3::decode(std::string message) const
    {
        std:: string result = "";
        for (char i: message)
        {
            if (isalpha(i))
            {
                result += i >= 'a' + 3 ? alphabet[i - 3] : nums['z' - 97 + i - 2];
            }
            else if (std::isdigit(i))
            {
                result += i >= 3 ? nums[i - 3] : nums[10 + i - 2];
            }
            else result += i;
        }
        return  result;
    }





