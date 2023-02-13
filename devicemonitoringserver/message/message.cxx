#include "message.hxx"
#include <cstdint>

dms::message::meterage::meterage(const std::uint64_t timestamp,
                                 const std::uint8_t value)
    : _timestamp{timestamp}, _value{value} {
}

dms::message::MSG_TYPE
dms::message::meterage::type(void) const {
    return MSG_TYPE::METERAGE;
}

std::uint64_t
dms::message::meterage::timestamp(void) const {
    return _timestamp;
}

std::uint8_t
dms::message::meterage::value(void) const {
    return _value;
}

dms::message::command::command(const std::int8_t value) : _value(value) {
}

dms::message::MSG_TYPE
dms::message::command::type(void) const {
    return MSG_TYPE::COMMAND;
}

std::int8_t
dms::message::command::value(void) const {
    return _value;
}

dms::message::error::error(const dms::message::ERR_TYPE err) : _err{err} {
}

dms::message::MSG_TYPE
dms::message::error::type(void) const {
    return MSG_TYPE::ERROR;
}

dms::message::ERR_TYPE
dms::message::error::err(void) const {
    return _err;
}
