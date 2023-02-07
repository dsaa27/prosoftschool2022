#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H
#include <string>

class BaseEncoderExecutor
{
public:
    virtual std::string encode(std::string message) = 0;
    virtual std::string decode(std::string message) = 0;
    virtual std::string name() = 0;
};
#endif // BASEENCODEREXECUTOR_H
