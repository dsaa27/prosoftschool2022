#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include "../common.h"

#include <string>
#include <sstream>
#include <iomanip>

class AbstractMessage
{
public:
    virtual ~AbstractMessage() = default;

    virtual std::string convert2string() const = 0;

    virtual Enumerations::MessageType getMessageType() const = 0;
};

struct MeterageMessage final : public AbstractMessage
{
    MeterageMessage (uint64_t timeStamp, uint8_t measureValue)
        :timeStamp(timeStamp), measureValue(measureValue) {}

    ~MeterageMessage() = default;

    std::string convert2string() const final
    {
        std::ostringstream ost;
        ost << static_cast<int>(Enumerations::MessageType::meterage) << " "
            << timeStamp << " " << static_cast<short>(measureValue);
        return ost.str();
    }

    Enumerations::MessageType getMessageType() const final
    {
        return Enumerations::MessageType::meterage;
    }

    uint64_t timeStamp = 0;
    uint8_t measureValue;
};

struct CommandMessage final : public AbstractMessage
{
    CommandMessage (double correction) : correction(correction) {}

    ~CommandMessage() = default;

    std::string convert2string() const final
    {
        std::ostringstream ost;
        ost << static_cast<int>(Enumerations::MessageType::command) << " "
            << std::setprecision(6) << correction;
        return ost.str();
    }

    Enumerations::MessageType getMessageType() const final
    {
        return Enumerations::MessageType::command;
    }

    double correction;
};

struct ErrorMessage final : public AbstractMessage
{
    ErrorMessage(Enumerations::ErrorType errorType) : errorType(errorType) {}

    ~ErrorMessage() = default;

    std::string convert2string() const final
    {
        std::ostringstream ost;
        ost << static_cast<int>(Enumerations::MessageType::error) << " "
            << static_cast<int>(errorType);
        return ost.str();
    }

    Enumerations::MessageType getMessageType() const final
    {
        return Enumerations::MessageType::error;
    }

    Enumerations::ErrorType errorType;
};

#endif // ABSTRACTMESSAGE_H
