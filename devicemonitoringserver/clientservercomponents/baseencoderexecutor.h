#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H

#include <string>

class BaseEncoderExecutor
{
public:
    virtual ~BaseEncoderExecutor() = default;

    virtual std::string encode(const std::string&) = 0;

    virtual std::string decode(const std::string&) = 0;

    virtual std::string name() = 0;
};

#endif // BASEENCODEREXECUTOR_H
