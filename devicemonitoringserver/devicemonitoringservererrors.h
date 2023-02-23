#ifndef DEVICEMONITORINGSERVERERRORS_H
#define DEVICEMONITORINGSERVERERRORS_H

#include "common.h"

#include <string>

enum class DeviceMonitoringServerErrEnum
{
    eDeserializeError = 101,
    eSerializeError = 102,
    eDecodeError = 201,
    eEncodeError = 202,
    eSetAlgorithmError = 301,
    eMessageTypeError = 401,
    eSetScheduleError = 501,
    eControlError = 601
};

class DeviceMonitoringServerErrors
{
    NON_COPYABLE(DeviceMonitoringServerErrors);
public:
    static const DeviceMonitoringServerErrors DESERIALIZE_ERROR;
    static const DeviceMonitoringServerErrors SERIALIZE_ERROR;
    static const DeviceMonitoringServerErrors DECODE_ERROR;
    static const DeviceMonitoringServerErrors ENCODE_ERROR;
    static const DeviceMonitoringServerErrors SET_ALGORITHM_ERROR;
    static const DeviceMonitoringServerErrors MESSAGE_TYPE_ERROR;
    static const DeviceMonitoringServerErrors SET_SCHEDULE_ERROR;
    static const DeviceMonitoringServerErrors CONTROL_ERROR;

    std::string formatString(const std::string& inform) const;
    void throwRunTimeError(const std::string& inform) const;

private:
    DeviceMonitoringServerErrors() = delete;
    DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum err, const std::string& message);

    const DeviceMonitoringServerErrEnum err;
    const uint64_t code;
    const std::string message;
};

#endif // DEVICEMONITORINGSERVERERRORS_H
