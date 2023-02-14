#ifndef METERAGEMESSAGE_H
#define METERAGEMESSAGE_H

#include "abstractmessage.h"

struct MeterageMessage final : public AbstractMessage
{
    MeterageMessage (uint64_t timeStamp, uint8_t measureValue)
        :timeStamp(timeStamp), measureValue(measureValue) {}

    MeterageMessage() : MeterageMessage(0, 0) {}

    std::string convert2string() const final;

    Enumerations::MessageType getMessageType() const final;

    uint64_t timeStamp = 0;
    uint8_t measureValue;
};

#endif // METERAGEMESSAGE_H
