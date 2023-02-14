#ifndef ROTX_H
#define ROTX_H
#include "baseencoderexecutor.h"

class RotX final: public BaseEncoderExecutor
{
public:
    RotX(unsigned int offset);
    std::string encode (const std::string& message) final;
    std::string decode (const std::string& message) final;
    std::string name () final;
private:
    std::string m_name = "ROT";
    const unsigned int m_offset;
};

#endif // ROTX_H
