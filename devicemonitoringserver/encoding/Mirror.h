#ifndef DEVICEMONITORINGSERVER_MIRROR_H
#define DEVICEMONITORINGSERVER_MIRROR_H


#include <string>
#include "BaseEncoderExecutor.h"

/*!
 * \brief класс для шифрования и дешифрования сообщений методом зеркала
 */
class Mirror final : public BaseEncoderExecutor
        {
public:
    Mirror() = default;
    std::string encode(std::string message) const final;
    std::string decode(std::string message) const final;
};


#endif //DEVICEMONITORINGSERVER_MIRROR_H
