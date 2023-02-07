#ifndef MIRROR_H
#define MIRROR_H
#include "baseencoderexecutor.h"

class Mirror : public BaseEncoderExecutor
{
public:
    std::string encode (std::string message) final;
    std::string decode (std::string message) final;
    std::string name () final;
private:
    std::string m_name = "Mirror";

};

#endif // MIRROR_H
