#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H

#include "message.h"

struct MessageSerializator {
    std::string& serialize(const Message* incoming);
    Message* deserialize(const std::string& incoming);
};

#endif // MESSAGESERIALIZATOR_H
