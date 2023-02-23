#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H

#include <iostream>

class BaseEncoderExecutor
{
public:
    virtual std::string encode(const std::string& message) const = 0;
    virtual std::string decode(const std::string& message) const = 0;
    virtual std::string getName() const = 0;

    virtual ~BaseEncoderExecutor() = default;
};

#endif // BASEENCODEREXECUTOR_H
