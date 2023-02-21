#pragma once
#include "../message/message.hxx"
#include <memory>
#include <string>

namespace dms {
    namespace serialization {
        class serializator;
    }
}

class dms::serialization::serializator {
  public:
    std::string
    serialize(const std::unique_ptr<const dms::message::message>&) const;

    std::unique_ptr<const dms::message::message>
    deserialize(const std::string& msg) const;
};
