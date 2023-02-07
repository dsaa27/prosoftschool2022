#ifndef ROT3_H
#define ROT3_H
#include "baseencoderexecutor.h"

class Rot3 : public BaseEncoderExecutor
{
public:
    std::string encode (std::string message) final;
    std::string decode (std::string message) final;
    std::string name () final;
private:
    std::string m_name = "ROT3";
};

#endif // ROT3_H
