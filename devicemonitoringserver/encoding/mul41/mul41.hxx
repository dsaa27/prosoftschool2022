#include "../base_encoder.hxx"

namespace dms {
namespace encoder {
class mul41;
}
} // namespace dms

class dms::encoder::mul41 : public dms::encoder::base_encoder {
  public:
    std::string
    encode(const std::string& message) const;

    std::string
    decode(const std::string& message) const;

    dms::encoder::ENC_TYPE
    name(void) const;

  private:
    char
    encode(const char) const;

    char
    decode(const char) const;
};
