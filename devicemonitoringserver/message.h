#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>

struct Message {
    enum Type{
        Meterage = 0,
        Command,
        Error,
        Info
    } const m_type;
protected:
    Message(Message::Type type): m_type{type} {};
public:
    virtual ~Message() = default;
};


struct Meterage: public Message {
    Meterage(const uint8_t value, const uint64_t timestamp): Message(Message::Type::Meterage),
        m_value(value), m_timestamp(timestamp) {};
    Meterage(): Message(Message::Type::Meterage) {};

    uint8_t m_value{};
    uint64_t m_timestamp{};
};


struct Command: public Message {
    Command(const uint8_t value, const bool up): Message(Message::Type::Command),
        m_value(value), m_up(up) {};
    Command(): Message(Message::Type::Command) {};

    uint8_t m_value{};
    bool m_up{false};
};


struct Error: public Message {
    enum Type{
        NoSchedule,
        NoTimestamp,
        Obsolete,
        ErrorMessage = 100
    } m_errType;
    Error(const Error::Type errType): Message(Message::Type::Error), m_errType(errType) {};
    Error(): Message(Message::Type::Error), m_errType(Error::Type::ErrorMessage) {};
};

struct Info: public Message {
    Info(const std::string& message): Message(Message::Type::Info), m_message(message) {};
    Info(): Message(Message::Type::Info) {};

    std::string m_message;
};

#endif // MESSAGE_H
