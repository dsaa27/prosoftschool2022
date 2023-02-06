#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include <string>
#include <sstream>
#include <cstdint>

#include "abstractmessage.h"
#include "../unit_tests_functions/unittestfunctions.h"


class MessageSerializer
{
    friend void unitTestFunctions::testCheckInvalidDeserializeMessageArgument(
            const std::string messageAsString,
            const std::string exceptionMessage);
public:
    MessageSerializer() = default;

    std::string serializeMessage (const AbstractMessage &other);

    AbstractMessage* deserializeMessage (const std::string &messageAsString);

private:
    void checkInvalidDeserializeMessageArgument(const std::string &messageAsString);

};

#endif // MESSAGESERIALIZER_H
