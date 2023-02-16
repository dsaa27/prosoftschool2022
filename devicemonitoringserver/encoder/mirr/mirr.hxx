#pragma once
#include "../base_encoder.hxx"

namespace dms {
    namespace encoder {
        class mirr;
    }
}

class dms::encoder::mirr : public dms::encoder::base_encoder {
  private:
    char encode(const char) const;
    char decode(const char) const;

  public:
    std::string
    encode(const std::string& message) const;

    std::string
    decode(const std::string& message) const;

    dms::encoder::ENC_TYPE
    name(void) const;
};
