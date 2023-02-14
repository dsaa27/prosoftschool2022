#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H

#include <string>
using std::string;

class BaseEncoderExecutor {
    public:

        virtual std::string encode(std::string message) = 0;
        virtual std::string decode(std::string message) = 0;
        virtual std::string getname() = 0;

};

#endif // BASEENCODEREXECUTOR_H
