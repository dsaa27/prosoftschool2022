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
        meterage = 1,
        command = 2,
        error = 3
    };

    enum class ErrorType
    {
        noSchedule = 1,
        noTimestamp = 2,
        obsolete = 3
    };
}

#endif // COMMON_H
