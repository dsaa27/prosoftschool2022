#ifndef DEVICEMONITORINGSERVER_BASEENCODEREXECUTOR_H
#define DEVICEMONITORINGSERVER_BASEENCODEREXECUTOR_H


#include <typeinfo>
#include <string>

class BaseEncoderExecutor {

public:
    /*!
    * \brief Зашифровать сообщение
    * \return зашифрованное сообщение
    */
    virtual std::string encode(std::string message) const = 0;
    /*!
    * \brief Дешифровать сообщение
     * \return дешифрованное сообщение
    */
    virtual std::string decode(std::string message) const = 0;
    /*!
    * \brief Получить имя метода шифрования
     * \return имя класса
    */
    std::string getName() const
    {
        return typeid(this).name();
    }
};


#endif //DEVICEMONITORINGSERVER_BASEENCODEREXECUTOR_H
