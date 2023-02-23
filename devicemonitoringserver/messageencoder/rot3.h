#ifndef ROT3_H
#define ROT3_H

#include "baseencoderexecutor.h"

class ROT3 final : public BaseEncoderExecutor
{
public:
    ROT3();

    std::string encode(const std::string& message) const final;
    std::string decode(const std::string& message) const final;
    std::string getName() const final;

private:
    std::string m_name;
};

#endif // ROT3_H
