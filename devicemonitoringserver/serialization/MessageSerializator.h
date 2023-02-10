#ifndef DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
#define DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H


#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include "deviceworkschedule.h"

/*!
 * \brief класс сериализации и десериализации сообщений
 */
class MessageSerializator {

public:
    MessageSerializator() = default;
    ~MessageSerializator() = default;

    /*!
    * \brief типы сообщений
    */
    enum messageType
    {
        Meterage = 0, // измерение
        Command = 1, // команда
        Error = 2 // ошибка
    };

    /*!
    * \brief результат десериализованного сообщения.
    */
    struct MessageStruct final
    {
        messageType type = messageType::Meterage; ///< Тип сообщения
        int64_t valueToCorrect = 0; ///< Значение, на которое нужно скорректировать параметр
        Phase phase = {0, 0}; ///< Текущий этап
        uint8_t errorCode = 0; ///< Код ошибки, если возникла
    };
    /*!
    * \brief сериализует сообщение
    * \param message - сообщение в виде структуры
    * \return величина корректировки для достижения этого плана или код ошибки в случае некорректных измерений
    */
    std::string serialize(MessageStruct message);
    /*!
    * \brief десереализует сообщение
    * \param message - сообщение
    * \return десеарилизованное сообщение в виде вектора
    */
    MessageStruct deserialize(const std::string& message) ;
};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
