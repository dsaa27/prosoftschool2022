#pragma once
#include <cstdint>

enum class MSG_TYPE : uint8_t { METERAGE = 0u, COMMAND, ERROR };

enum class ERR_TYPE : uint8_t { NOSCHEDULE = 0u, NOTIMESTAMP, OBSOLETE };

struct message {
  public:
    virtual MSG_TYPE type(void) const = 0;
    virtual ~message(void) = default;
};

struct meterage : message {
  private:
    uint64_t _timestamp;
    uint64_t _value;

  public:
    meterage(const uint64_t timestamp, const uint64_t value)
        : _timestamp{timestamp}, _value{value} {
    }

    MSG_TYPE type(void) const {
        return MSG_TYPE::METERAGE;
    }

    ~meterage(void) = default;
};

struct command : message {
  public:
    uint64_t _value;

    MSG_TYPE type(void) const {
        return MSG_TYPE::COMMAND;
    }

    command(const uint64_t value) : _value(value) {
    }

    ~command(void) = default;
};

struct error : message {
    ERR_TYPE err;

    MSG_TYPE type(void) const {
        return MSG_TYPE::ERROR;
    }

    ~error(void) = default;
};
