#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include "../../common.h"

#include <string>
#include <sstream>
#include <iomanip>

struct AbstractMessage
{
    virtual ~AbstractMessage() = default;

    virtual std::string convert2string() const = 0;

    virtual Enumerations::MessageType getMessageType() const = 0;
};

#endif // ABSTRACTMESSAGE_H
