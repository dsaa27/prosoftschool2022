#include "devicemockerrors.h"

#include <stdexcept>

const DeviceMockErrors DeviceMockErrors::DESERIALIZE_ERROR =
        DeviceMockErrors(DeviceMockErrEnum::eDeserializeError, "Deserialize error");

const DeviceMockErrors DeviceMockErrors::SERIALIZE_ERROR =
        DeviceMockErrors(DeviceMockErrEnum::eSerializeError, "Serialize error");

const DeviceMockErrors DeviceMockErrors::DECODE_ERROR =
        DeviceMockErrors(DeviceMockErrEnum::eDecodeError, "Decode error");

const DeviceMockErrors DeviceMockErrors::ENCODE_ERROR =
        DeviceMockErrors(DeviceMockErrEnum::eEncodeError, "Encode error");

const DeviceMockErrors DeviceMockErrors::SET_ALGORITHM_ERROR =
        DeviceMockErrors(DeviceMockErrEnum::eSetAlgorithmError, "Error setting the encoding algorithm");

const DeviceMockErrors DeviceMockErrors::MESSAGE_TYPE_ERROR =
        DeviceMockErrors(DeviceMockErrEnum::eMessageTypeError, "Unexpected message type");


DeviceMockErrors::DeviceMockErrors(DeviceMockErrEnum err, const std::string& message) :
    err(err), code(static_cast<int>(err)), message(message)
{}

std::string DeviceMockErrors::formatString(const std::string& inform) const
{
    return "[Device] (" + std::to_string(code) + ") " + message + ": " + inform;
}

void DeviceMockErrors::throwRunTimeError(const std::string &inform) const
{
    throw std::runtime_error(formatString(inform));
}
