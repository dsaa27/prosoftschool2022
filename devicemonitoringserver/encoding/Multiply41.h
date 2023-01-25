#ifndef DEVICEMONITORINGSERVER_MULTIPLY41_H
#define DEVICEMONITORINGSERVER_MULTIPLY41_H


#include "BaseEncoderExecutor.h"

/*!
 * \brief класс для шифрования и дешифрования сообщений методом умножения на 41.
 */
class Multiply41 final : public BaseEncoderExecutor{
public:
    Multiply41()=default;
    std::string encode(std::string message) const final;
    std::string decode(std::string message) const final;
};


#endif //DEVICEMONITORINGSERVER_MULTIPLY41_H
