#ifndef MULTIPLY41_H
#define MULTIPLY41_H

#include "baseencoderexecutor.h"

class Multiply41 final : public BaseEncoderExecutor
{
public:
    Multiply41();

    std::string encode(const std::string& message) const final;
    std::string decode(const std::string& message) const final;
    std::string getName() const final;

private:
    std::string m_name;
};

#endif // MULTIPLY41_H
