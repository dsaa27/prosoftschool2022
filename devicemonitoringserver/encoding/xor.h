#ifndef XOR_H
#define XOR_H

#include <string>
#include "BaseEncoderExecutor.h"

/*!
 * \brief класс для шифрования и дешифрования сообщений методом xor
 */
class Xor : public BaseEncoderExecutor
{
public:
    Xor()=default;
    ~Xor()=default;
public:
    std::string encode(const std::string &message) const;
    std::string decode(const std::string &message) const;
    std::string getName() const;
};

#endif // XOR_H
