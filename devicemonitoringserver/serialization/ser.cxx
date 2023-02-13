#include "ser.hxx"
#include "../message/message.hxx"
#include <memory>
#include <string>

std::string
serializator::serialize(const dms::message::message* const msg) const {
    if (!msg) {
        return "";
    }

    std::string ret{};

    switch (msg->type()) {
    case dms::message::MSG_TYPE::COMMAND: {
        auto const cmd = dynamic_cast<const dms::message::command* const>(msg);

        if (!cmd) {
            return "";
        }

        ret += static_cast<char>(msg->type());
        ret += std::to_string(cmd->value());

        return ret;
    }

    case dms::message::MSG_TYPE::METERAGE: {
        auto const met = dynamic_cast<const dms::message::meterage* const>(msg);

        if (nullptr == met) {
            return "";
        }

        ret += static_cast<char>(msg->type());
        ret += std::to_string(met->timestamp());
        ret += ' ';
        ret += std::to_string(met->value());

        return ret;
    }

    case dms::message::MSG_TYPE::ERROR: {
        auto const err = dynamic_cast<const dms::message::error* const>(msg);

        if (!err) {
            return "";
        }

        ret += static_cast<char>(err->type());
        ret += static_cast<char>(err->err());
        return ret;
    }

    default:
        return "";
    }

    return "";
}

std::unique_ptr<const dms::message::message>
serializator::deserialize(const std::string& msg) const {
    const auto msg_type = static_cast<dms::message::MSG_TYPE>(msg[0]);

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
