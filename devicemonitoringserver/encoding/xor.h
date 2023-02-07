#ifndef XOR_H
#define XOR_H

#include <string>
#include "BaseEncoderExecutor.h"


class Xor : public BaseEncoderExecutor
{
public:
    Xor()=default;
    ~Xor()=default;
    // BaseEncoderExecutor interface
public:
    std::string encode(const std::string &message) const;
    std::string decode(const std::string &message) const;
    std::string getName() const;
};

#endif // XOR_H
