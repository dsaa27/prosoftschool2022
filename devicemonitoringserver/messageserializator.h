#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H

#include "message.h"

class MessageSerializator {
public:
    std::string serialize(const Message* incoming);
    Message* deserialize(const std::string& incoming);
};

#endif // MESSAGESERIALIZATOR_H
