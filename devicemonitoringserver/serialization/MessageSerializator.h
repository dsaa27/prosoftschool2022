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
    enum messageType
    {
        Meterage = 0,
        Command = 1,
        Error = 2
    };
    /*!
    * \brief результат десериализованного сообщения.
    */
    struct MessageStruct final
    {
        messageType type = messageType::Meterage; ///< Тип сообщения
        uint8_t valueToCorrect = 0; ///< Значение, на которое нужно скорректировать параметр
        Phase phase = {0, 0}; ///< Текущий этап
        uint8_t errorCode = 0; ///< Код ошибки, если возникла
    };
    /*!
    * \brief сериализует сообщение
    * \param messType - тип сообщения
    * \param errorCode - тип ошибки

    * \return величина корректировки для достижения этого плана или код ошибки в случае некорректных измерений
    */
    std::string serialize(messageType messType, uint8_t errorCode = 0, uint64_t timeStamp = 0,
                                 uint8_t value = 0);
    /*!
    * \brief десереализует сообщение
    * \param message - сообщение
    * \return десеарилизованное сообщение в виде вектора
    */
    MessageStruct deserialize(const std::string& message) ;
};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
