#pragma once
#include <cstdint>

enum class MSG_TYPE : std::uint8_t { METERAGE = 0u, COMMAND, ERROR };

enum class ERR_TYPE : std::uint8_t { NOSCHEDULE = 0u, NOTIMESTAMP, OBSOLETE };

struct message {
  public:
    virtual MSG_TYPE type(void) const = 0;
    virtual ~message(void) = default;
};

struct meterage : message {
  private:
    std::uint64_t _timestamp;
    std::uint8_t _value;

  public:
    meterage(const std::uint64_t timestamp, const std::uint8_t value)
        : _timestamp{timestamp}, _value{value} {
    }

    MSG_TYPE type(void) const {
        return MSG_TYPE::METERAGE;
    }

    std::uint64_t timestamp(void) const {
        return _timestamp;
    }

    std::uint8_t value(void) const {
        return _value;
    }

    ~meterage(void) = default;
};

struct command : message {
  private:
    std::int8_t _value;

  public:
    MSG_TYPE type(void) const {
        return MSG_TYPE::COMMAND;
    }

    std::int8_t value(void) const {
        return _value;
    }

    command(const std::int8_t value) : _value(value) {
    }

    ~command(void) = default;
};

struct error : message {
  private:
    ERR_TYPE _err;

  public:
    MSG_TYPE type(void) const {
        return MSG_TYPE::ERROR;
    }

    ERR_TYPE err(void) const {
        return _err;
    }

    error(const ERR_TYPE err) : _err{err} {
    }

    ~error(void) = default;
};
