#include "ser.hxx"
#include "../message.hxx"
#include <cstring>
#include<iostream>
#include <string>
#include <memory>

std::string serializator::serialize(const message* const msg) const {
    std::string ret;

    switch (msg->type()) {
    case MSG_TYPE::COMMAND: {
        auto const cmd = reinterpret_cast<const command* const>(msg);

        ret += static_cast<char>(msg->type());
        ret += std::to_string(cmd->_value);
        return ret;
    }

    case MSG_TYPE::METERAGE:
        break;

    case MSG_TYPE::ERROR:
        break;
    }

    return nullptr;
}

std::unique_ptr<message>
serializator::deserialize(const std::string& msg) const {
    const auto msg_type{(MSG_TYPE)msg[0]};

    switch (msg_type) {
    case MSG_TYPE::COMMAND: {
        uint64_t value = std::stoull(std::string(msg.begin() + 1, msg.end()));
        return std::unique_ptr<message>(new command(value));
    }
    default: {
    }
    }
    return nullptr;
}

