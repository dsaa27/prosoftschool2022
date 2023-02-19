#include "meteragemessage.h"

std::string MeterageMessage::convert2string() const
{
    std::ostringstream ost;
    ost << static_cast<int>(Enumerations::MessageType::meterage) << " "
        << timeStamp << " " << static_cast<short>(measureValue);
    return ost.str();
}

Enumerations::MessageType MeterageMessage::getMessageType() const
{
    return Enumerations::MessageType::meterage;
}
