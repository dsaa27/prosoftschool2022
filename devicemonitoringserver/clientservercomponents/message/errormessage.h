#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include "abstractmessage.h"

struct ErrorMessage final : public AbstractMessage
{
    ErrorMessage(Enumerations::ErrorType errorType) : errorType(errorType) {}

    ErrorMessage() : ErrorMessage(Enumerations::ErrorType::noSchedule) {}

    std::string convert2string() const final;

    Enumerations::MessageType getMessageType() const final;

    Enumerations::ErrorType errorType;
};

#endif // ERRORMESSAGE_H
