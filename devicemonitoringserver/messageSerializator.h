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
    std::string serializate(const MessageStruct& message);
    MessageStruct deSerializate(std::string serialMessage);
};
#endif // MESSAGESERIALIZATOR_H
