#ifndef MIRROR_H
#define MIRROR_H
#include "baseencoderexecutor.h"

class Mirror final : public BaseEncoderExecutor
{
public:
    std::string encode (const std::string& message) final;
    std::string decode (const std::string& message) final;
    std::string name () final;
private:
    std::string m_name = "Mirror";

};

#endif // MIRROR_H
