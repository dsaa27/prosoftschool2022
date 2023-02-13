#pragma once
#include <cstdint>

namespace dms {
namespace message {
enum class MSG_TYPE : std::uint8_t { METERAGE = 0u, COMMAND, ERROR };
enum class ERR_TYPE : std::uint8_t { NOSCHEDULE = 0u, NOTIMESTAMP, OBSOLETE };
class message;
class meterage;
class command;
class error;
} // namespace message
}; // namespace dms

class dms::message::message {
  public:
    virtual dms::message::MSG_TYPE
    type(void) const = 0;

    virtual ~message(void) = default;
};

class dms::message::meterage : public dms::message::message {
  private:
    std::uint64_t _timestamp{0u};
    std::uint8_t _value{0u};

  public:
    dms::message::MSG_TYPE
    type(void) const;

    std::uint64_t
    timestamp(void) const;

    std::uint8_t
    value(void) const;

    meterage(const std::uint64_t timestamp, const std::uint8_t value);
};

class dms::message::command : public dms::message::message {
  private:
    std::int8_t _value;

  public:
    dms::message::MSG_TYPE
    type(void) const;

    std::int8_t
    value(void) const;

    command(const std::int8_t value);
};

struct dms::message::error : dms::message::message {
  private:
    dms::message::ERR_TYPE _err;

  public:
    dms::message::MSG_TYPE
    type(void) const;

    dms::message::ERR_TYPE
    err(void) const;

    error(const dms::message::ERR_TYPE err);
};
