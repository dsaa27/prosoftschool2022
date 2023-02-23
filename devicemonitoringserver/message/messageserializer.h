#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include "message/message.h"

#include <iostream>

class MessageSerializer final
{
public:
    MessageSerializer() = default;
    ~MessageSerializer() = default;

    bool serialize(const MessageDto& messageDto, std::string& message) const;
    bool deserialize(const std::string& message, MessageDto& messageDto) const;
};

#endif // MESSAGESERIALIZER_H
