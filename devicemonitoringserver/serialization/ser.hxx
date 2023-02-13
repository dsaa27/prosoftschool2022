#pragma once
#include "../message/message.hxx"
#include <memory>
#include <string>

class serializator {
  public:
    std::string
    serialize(const dms::message::message* const) const;

    std::unique_ptr<const dms::message::message>
    deserialize(const std::string& msg) const;
};
