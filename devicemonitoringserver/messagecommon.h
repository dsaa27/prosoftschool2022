#ifndef MESSAGECOMMON_H
#define MESSAGECOMMON_H
#include <deviceworkschedule.h>
#include <cstdint>
enum messageType
{
    METERAGE,
    COMMAND,
    ERROR
};

enum errorType
{
    NO_SCHEDULE,
    NO_TIMESTAMP,
    OBSOLETE
};

struct MessageStruct
{
    short messageType = 0;
    Phase measurements;
    int adjustment = 0;
    uint8_t errorType = 0;
};

#endif // MESSAGECOMMON_H
