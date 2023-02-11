#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include <string>
#include <sstream>
#include <cstdint>

#include "abstractmessage.h"
#include "../unittest/unittest.h"


class MessageSerializer
{
    friend void unitTest::deserialization::catchInvalidArgumentException(
            std::string &receivedExceptionMessage, const std::string& wrongDeserializeMessage);

public:
    MessageSerializer() = default;

    std::string serializeMessage (const AbstractMessage &other);

    AbstractMessage* deserializeMessage (const std::string &messageAsString);

private:
    void checkInvalidDeserializeMessageArgument(const std::string &messageAsString);

};

#endif // MESSAGESERIALIZER_H
