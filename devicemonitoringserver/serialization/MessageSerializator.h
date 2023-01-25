#ifndef DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
#define DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H


#include <string>
#include <sstream>
#include <cstring>
#include <vector>

class MessageSerializator {
public:

    MessageSerializator();
    ~MessageSerializator();
    enum messageType
    {
        Meterage = 0,
        Command = 1,
        Error = 2
    };

    /*!
   * \brief сериализует сообщение
   * \param messType - тип сообщения
   * \param errType - тип ошибки

   * \return величина корректировки для достижения этого плана или код ошибки в случае некорректных измерений
   */
    static std::string serialize(messageType messType, uint8_t errType = -1, uint64_t timeStamp = -1,
                          uint8_t value = -1);
    /*!
   * \brief десереализует сообщение
   * \param message - сообщение
    * \return десеарилизованное сообщение в виде вектора
   */
    static std::vector<uint64_t> deserialize(const std::string& message) ;

};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
