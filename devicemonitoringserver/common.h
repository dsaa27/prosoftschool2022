#ifndef COMMON_H
#define COMMON_H

#define NON_COPYABLE(ClassName)           \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete;

#define UNUSED(x) (void)(x)


namespace Enumerations
{
    enum class MessageType
    {
        meterage = 0,
        command = 1,
        error = 2
    };

    enum class ErrorType
    {
        noSchedule = 0,
        noTimestamp = 1,
        obsolete = 2
    };
}

#endif // COMMON_H
