#pragma once
#include "../message.hxx"
#include <memory>
#include <string>

class serializator {
  public:

    std::string
    serialize(const message* const) const;

    std::unique_ptr<const message>
    deserialize(const std::string& msg) const;
};
