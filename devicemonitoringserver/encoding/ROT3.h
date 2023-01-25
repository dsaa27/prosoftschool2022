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
    ROT3();
    ~ROT3();
    std::string encode(std::string message) const final;

    std::string decode(std::string message) const final;
private:
    std::vector<char> alphabet;
    std::vector<int> nums;

};


#endif //DEVICEMONITORINGSERVER_ROT3_H
