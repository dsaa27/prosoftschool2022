#ifndef DEVICEMONITORINGSERVER_ROT3_H
#define DEVICEMONITORINGSERVER_ROT3_H


#include <vector>
#include "BaseEncoderExecutor.h"

/*!
 * \brief класс для шифрования и дешифрования сообщений методом шифра Цезаря со сдвигом 3.
 */
class ROT3 final : public BaseEncoderExecutor
        {
public:
    ROT3() = default;
    ~ROT3() = default;
    std::string encode(const std::string& message) const final;

    std::string decode(const std::string& message) const final;
    std::string getName() const final;
};


#endif //DEVICEMONITORINGSERVER_ROT3_H
