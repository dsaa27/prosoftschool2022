#ifndef DEVICEMOCKERRORS_H
#define DEVICEMOCKERRORS_H

#include "common.h"

#include <string>

enum class DeviceMockErrEnum
{
    eDeserializeError = 101,
    eSerializeError = 102,
    eDecodeError = 201,
    eEncodeError = 202,
    eSetAlgorithmError = 301,
    eMessageTypeError = 401
};

class DeviceMockErrors
{
    NON_COPYABLE(DeviceMockErrors);
public:
    static const DeviceMockErrors DESERIALIZE_ERROR;
    static const DeviceMockErrors SERIALIZE_ERROR;
    static const DeviceMockErrors DECODE_ERROR;
    static const DeviceMockErrors ENCODE_ERROR;
    static const DeviceMockErrors SET_ALGORITHM_ERROR;
    static const DeviceMockErrors MESSAGE_TYPE_ERROR;

    std::string formatString(const std::string& inform) const;
    void throwRunTimeError(const std::string& inform) const;

private:
    DeviceMockErrors() = delete;
    DeviceMockErrors(DeviceMockErrEnum err, const std::string& message);

    const DeviceMockErrEnum err;
    const uint64_t code;
    const std::string message;
};

#endif // DEVICEMOCKERRORS_H
