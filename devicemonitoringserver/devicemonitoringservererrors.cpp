#include "devicemonitoringservererrors.h"
#include <stdexcept>

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::DESERIALIZE_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eDeserializeError, "Deserialize error");

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::SERIALIZE_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eSerializeError, "Serialize error");

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::DECODE_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eDecodeError, "Decode error");

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::ENCODE_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eEncodeError, "Encode error");

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::SET_ALGORITHM_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eSetAlgorithmError, "Error setting the encoding algorithm");

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::MESSAGE_TYPE_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eMessageTypeError, "Unexpected message type");

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::SET_SCHEDULE_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eSetScheduleError, "Device with this `deviceId` already exists");

const DeviceMonitoringServerErrors DeviceMonitoringServerErrors::CONTROL_ERROR =
        DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum::eControlError, "Unexpected control type");


DeviceMonitoringServerErrors::DeviceMonitoringServerErrors(DeviceMonitoringServerErrEnum err, const std::string& message) :
    err(err), code(static_cast<int>(err)), message(message)
{}

std::string DeviceMonitoringServerErrors::formatString(const std::string& inform) const
{
    return "[Server] (" + std::to_string(code) + ") " + message + ": " + inform;
}

void DeviceMonitoringServerErrors::throwRunTimeError(const std::string &inform) const
{
    throw std::runtime_error(formatString(inform));
}
