#pragma once
#include "../message.hxx"
#include <string>
#include<memory>

class serializator {
  public:
    std::string serialize(const message* const) const;
    std::unique_ptr<message> deserialize(const std::string& msg) const;
};
