#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H
#include <string>
#include <sstream>
#include <deviceworkschedule.h>
#include <iostream>
#include <messagecommon.h>

class MessageSerializer
{
public:
    /*!
     * \brief Конвертировать структуру сообщения в строку.
     */
    std::string serializate(const MessageStruct& message);
    /*!
     * \brief Конвертировать строку в структуру сообщения.
     */
    MessageStruct deserializate(const std::string &serialMessage);
};

#endif // MESSAGESERIALIZATOR_H
