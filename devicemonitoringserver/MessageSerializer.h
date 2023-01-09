#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include "common.h"

#include <string>
#include <vector>

class AbstractMessageHandler;

/*!
 * \brief Класс, создающий сообщения
 */
class MessageSerialiser
{
    NON_COPYABLE(MessageSerialiser)
public:
    /*!
     * \brief Конструктор.
     * \param Message - владеющий указатель на объект класса сериализатора сообщения
     */
    MessageSerialiser(AbstractMessageHandler* Message);
    ~MessageSerialiser();






private:
    AbstractMessageHandler* m_Message = nullptr;
};





#endif // MESSAGESERIALIZER_H
