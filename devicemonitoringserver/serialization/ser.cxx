#include "ser.hxx"
#include "../message.hxx"
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

std::string serializator::serialize(const message* const msg) const {
    if (nullptr == msg) {
        return "";
    }

    std::string ret{};

    switch (msg->type()) {
    case MSG_TYPE::COMMAND: {
        auto const cmd = dynamic_cast<const command* const>(msg);

        if (nullptr == cmd) {
            return "";
        }

        ret += static_cast<char>(msg->type());
        ret += std::to_string(cmd->value());

        return ret;
    }

    case MSG_TYPE::METERAGE: {
        auto const met = dynamic_cast<const meterage* const>(msg);

        if (nullptr == met) {
            return "";
        }

        ret += static_cast<char>(msg->type());
        ret += std::to_string(met->timestamp());
        ret += ',';
        ret += std::to_string(met->value());

        return ret;
    }

    case MSG_TYPE::ERROR: {
        auto const err = dynamic_cast<const error* const>(msg);

        if (nullptr == err) {
            return "";
        }

        ret  += static_cast<char>(err->type());
        ret += static_cast<char>(err->err());
        return ret;
    }

    default:
        return "";
    }

    return "";
}

std::unique_ptr<message>
serializator::deserialize(const std::string& msg) const {
    const auto msg_type{static_cast<MSG_TYPE>(msg[0])};

    switch (msg_type) {

    case MSG_TYPE::COMMAND: {
        const int8_t value{static_cast<int8_t>(
            std::stoi(std::string{msg.begin() + 1, msg.end()}))};

        return std::unique_ptr<message>{new command(value)};
    }

    case MSG_TYPE::METERAGE: {
        const std::string::size_type splitter_pos{msg.find(',')};

        if (std::string::npos == splitter_pos) {
            return nullptr;
        }

        const uint64_t timestamp{std::stoull(
            std::string{msg.begin() + 1, msg.begin() + splitter_pos})};

        const uint64_t value{std::stoull(
            std::string{msg.begin() + splitter_pos + 1, msg.end()})};

        return std::unique_ptr<message>{new meterage(timestamp, value)};
    }

    case MSG_TYPE::ERROR: {
        const ERR_TYPE err{static_cast<ERR_TYPE>(msg[1])};
        return std::unique_ptr<message>{new error(err)};
    }

    default:
        return nullptr;
    }

    return nullptr;
}
