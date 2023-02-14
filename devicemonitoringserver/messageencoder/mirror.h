#ifndef MIRROR_H
#define MIRROR_H

#include "baseencoderexecutor.h"

class Mirror final : public BaseEncoderExecutor
{
public:
    Mirror();

    std::string encode(const std::string& message) const final;
    std::string decode(const std::string& message) const final;
    std::string getName() const final;

private:
    std::string m_name;
};

#endif // MIRROR_H
