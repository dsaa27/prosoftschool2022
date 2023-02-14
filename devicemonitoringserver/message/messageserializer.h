#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include "message/message.h"
#include <iostream>

class MessageSerializer final
{
public:
    std::string serialize(const MessageDto& messageDto) const;
    MessageDto deserialize(const std::string& message) const;
};

#endif // MESSAGESERIALIZER_H
