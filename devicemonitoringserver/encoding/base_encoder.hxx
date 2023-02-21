#pragma once
#include <cstdint>
#include <string>

namespace dms {
namespace encoder {
enum class ENC_TYPE : std::uint8_t { MIRR = 0u, MUL41, ROT3 };
class base_encoder;
} // namespace encoder
} // namespace dms

// encoder
class dms::encoder::base_encoder {
  public:
    virtual std::string
    encode(const std::string& message) const = 0;

    virtual std::string
    decode(const std::string& message) const = 0;

    virtual dms::encoder::ENC_TYPE
    name(void) const = 0;

    virtual ~base_encoder(void) = default;
};
