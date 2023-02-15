#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include "common.h"

#include <string>
#include <vector>


/*!
 * \brief Класс, создающий сообщения
 */
class MessageSerialiser
{

public:
    /*!
     * \brief Создать сообщение со значением переменной
     * \param meterages - значение передаваемого измеряемого параметра
     * \param timeStamp - значение метки времени передаваемого измеряемого параметра
     */
    std::string serialize_Message(const uint8_t &meterages, const uint64_t &timeStamp);

    /*!
     * \brief Создать командное сообщение
     * \param command - значение поправочной команды
     */
    std::string serialize_Message(const double &command);


    /*!
     * \brief Создать сообщение об ошибке
     * \param type_error - название передаваемой ошибки
     */
    std::string serialize_Message(const std::string &type_error);


    /*!
     * \brief Распарсить сообщение (функция для отладки)
     * \param message - сообщение, которое нужно распарсить
     */
    void deserialize_Message(const std::string &message);

    /*!
     * \brief Вернуть тип передаваемого сообщения (строка)
     * \param message - сообщение, которое нужно распарсить
     */
    std::string GetTypeMessage(const std::string &message);

    /*!
     * \brief Вернуть значение измерения
     * \param message - сообщение, которое нужно распарсить
     */
    uint8_t GetMeterage(const std::string &message);

    /*!
     * \brief Вернуть метку времени
     * \param message - сообщение, которое нужно распарсить
     */
    uint64_t GetTimeStamp(const std::string &message);

    /*!
     * \brief Вернуть тип ошибки
     * \param message - сообщение, которое нужно распарсить
     */
    std::string GetTypeError(const std::string &message);

    /*!
     * \brief Вернуть значение команды
     * \param message - сообщение, которое нужно распарсить
     */
    double GetCommand(const std::string &message);

private:
    std::string writtenMessage;
};


#endif // MESSAGESERIALIZER_H
