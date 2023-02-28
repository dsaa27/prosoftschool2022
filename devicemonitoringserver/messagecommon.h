#ifndef MESSAGECOMMON_H
#define MESSAGECOMMON_H
#include <deviceworkschedule.h>
#include <cstdint>
enum messageType
{
    METERAGE,
    COMMAND,
    ERROR,
    NO_TYPE
};

enum errorType
{
    NO_SCHEDULE,
    NO_TIMESTAMP,
    OBSOLETE,
    NO_ERROR
};

typedef int adjustment_t;

struct MessageStruct
{
    MessageStruct() = default;
    MessageStruct(errorType error) : messageType(ERROR), errorType(error) {}
    MessageStruct(Phase meterage) : messageType(METERAGE), measurements(meterage){}
    MessageStruct(adjustment_t adj) : messageType(COMMAND), adjustment(adj){}
    short messageType = NO_TYPE;
    Phase measurements;
    adjustment_t adjustment = 0;
    uint8_t errorType = 0;
};

#endif // MESSAGECOMMON_H
