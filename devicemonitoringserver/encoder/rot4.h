#ifndef ROT4_H
#define ROT4_H
#include "baseencoderexecutor.h"

class Rot4 : public BaseEncoderExecutor
{
public:
    std::string encode (std::string message) final;
    std::string decode (std::string message) final;
    std::string name () final;
private:
    std::string m_name = "ROT4";
};
#endif // ROT4_H
