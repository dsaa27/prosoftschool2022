#include "commandmessage.h"

std::string CommandMessage::convert2string() const
{
    std::ostringstream ost;
    ost << static_cast<int>(Enumerations::MessageType::command) << " "
        << std::setprecision(6) << correction;
    return ost.str();
}

Enumerations::MessageType CommandMessage::getMessageType() const
{
    return Enumerations::MessageType::command;
}
