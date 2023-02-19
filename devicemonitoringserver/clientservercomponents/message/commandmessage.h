#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include "abstractmessage.h"

struct CommandMessage final : public AbstractMessage
{
    CommandMessage (double correction) : correction(correction) {}

    CommandMessage() : CommandMessage(0) {}

    std::string convert2string() const final;

    Enumerations::MessageType getMessageType() const final;

    double correction;
};
#endif // COMMANDMESSAGE_H
