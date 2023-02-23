#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>

enum MessageType
{
    eMeterage,
    eCommand,
    eError
};

enum ErrorType
{
    eUnknown,
    eNoSchedule,
    eNoTimestamp,
    eObsolete
};

struct Meterage
{
    uint64_t timeStamp = 0; ///< Метка времени измерения
    uint8_t value = 0;      ///< Значение измерения
};

struct MessageDto
{
    MessageType messageType = MessageType::eError;
    ErrorType errorType = ErrorType::eUnknown;
    int64_t parameterTuning = 0;
    Meterage meterage;
};

#endif // MESSAGE_H
