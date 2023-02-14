#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>

enum MessageType
{
    Meterage,
    Command,
    Error
};

enum ErrorType
{
    Unknown,
    NoSchedule,
    NoTimestamp,
    Obsolete
};

struct Meterage
{
    uint64_t timeStamp = 0; ///< Метка времени измерения
    uint8_t value = 0;      ///< Значение измерения
};

struct MessageDto
{
    MessageType messageType = MessageType::Error;
    ErrorType errorType = ErrorType::Unknown;
    int64_t parameterTuning = 0;
    struct Meterage meterage;
};

#endif // MESSAGE_H
