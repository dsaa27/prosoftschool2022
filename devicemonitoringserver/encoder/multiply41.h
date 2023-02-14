#ifndef MULTIPLY41_H
#define MULTIPLY41_H
#include "baseencoderexecutor.h"

class Multiply41 final : public BaseEncoderExecutor
{
public:
    std::string encode (const std::string& message) final;
    std::string decode (const std::string& message) final;
    std::string name() final;
private:
    std::string m_name = "Multiply41";
};
#endif // MULTIPLY41_H
