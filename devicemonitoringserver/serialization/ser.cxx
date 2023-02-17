#include "ser.hxx"
#include "../message/message.hxx"
#include <memory>
#include <string>

std::string
dms::serialization::serializator::serialize(
    const std::unique_ptr<const dms::message::message>& msg) const {

    if (nullptr == msg) {
        return {};
    }

    std::string ret{};

    switch (msg->type()) {
    case dms::message::MSG_TYPE::COMMAND: {
        const dms::message::command* const command{
            dynamic_cast<const dms::message::command*>(msg.get())};

        if (nullptr == command) {
            return {};
        }

        ret += static_cast<char>(msg->type());
        ret += std::to_string(command->value());

        return ret;
    }

    case dms::message::MSG_TYPE::METERAGE: {
        const dms::message::meterage* const meterage{
            dynamic_cast<const dms::message::meterage* const>(msg.get())};

        if (nullptr == meterage) {
            return {};
        }

        ret += static_cast<char>(msg->type());
        ret += std::to_string(meterage->timestamp());
        ret += ' ';
        ret += std::to_string(meterage->value());

        return ret;
    }

    case dms::message::MSG_TYPE::ERROR: {
        auto const err =
            dynamic_cast<const dms::message::error* const>(msg.get());

        if (nullptr == err) {
            return {};
        }

        ret += static_cast<char>(err->type());
        ret += static_cast<char>(err->err());

        return ret;
    }
    }

    return {};
}

std::unique_ptr<const dms::message::message>
dms::serialization::serializator::deserialize(const std::string& msg) const {
    const dms::message::MSG_TYPE msg_type{
        static_cast<dms::message::MSG_TYPE>(msg[0])};

    switch (msg_type) {

    case dms::message::MSG_TYPE::COMMAND: {
        const std::int8_t value{static_cast<int8_t>(
            std::stoi(std::string{msg.begin() + 1, msg.end()}))};

        return std::make_unique<const dms::message::command>(value);
    }

    case dms::message::MSG_TYPE::METERAGE: {
        const std::string::size_type splitter_pos{msg.find(' ')};

        if (std::string::npos == splitter_pos) {
            return nullptr;
        }

        const std::uint64_t timestamp{std::stoull(
            std::string{msg.begin() + 1, msg.begin() + splitter_pos})};

        const std::uint8_t value{static_cast<std::uint8_t>(
            std::stoi(std::string{msg.begin() + splitter_pos + 1, msg.end()}))};

        return std::make_unique<const dms::message::meterage>(timestamp, value);
    }

    case dms::message::MSG_TYPE::ERROR: {
        const dms::message::ERR_TYPE err{
            static_cast<const dms::message::ERR_TYPE>(msg[1])};

        return std::make_unique<const dms::message::error>(err);
    }

    default:
        return nullptr;
    }

    return nullptr;
}
