#include "errormessage.h"

std::string ErrorMessage::convert2string() const
{
    std::ostringstream ost;
    ost << static_cast<int>(Enumerations::MessageType::error) << " "
        << static_cast<int>(errorType);
    return ost.str();
}

Enumerations::MessageType ErrorMessage::getMessageType() const
{
    return Enumerations::MessageType::error;
}
