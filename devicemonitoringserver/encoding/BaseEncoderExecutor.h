#ifndef DEVICEMONITORINGSERVER_BASEENCODEREXECUTOR_H
#define DEVICEMONITORINGSERVER_BASEENCODEREXECUTOR_H

#include <string>
/*!
 * Базовый абстрактный класс для шифрования и дешифрования
 */
class BaseEncoderExecutor
        {

public:
    virtual ~BaseEncoderExecutor() = default;
    /*!
    * \brief Зашифровать сообщение
    * \param message - сообщение
    * \return зашифрованное сообщение
    */
    virtual std::string encode(const std::string& message) const = 0;
    /*!
    * \brief Дешифровать сообщение
    * \param message - сообщение
    * \return дешифрованное сообщение
    */
    virtual std::string decode(const std::string& message) const = 0;

    /*!
    * \brief Получить имя метода шифрования
    * \return имя класса
    */
    virtual std::string getName() const = 0;
};


#endif //DEVICEMONITORINGSERVER_BASEENCODEREXECUTOR_H
