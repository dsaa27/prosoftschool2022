#pragma once
#include "../base_encoder.hxx"

namespace dms {
    namespace encoder {
        class mirr;
    }
}

class dms::encoder::mirr : public dms::encoder::base_encoder {
  private:
    static const std::string _name;

  public:
    std::string
    encode(const std::string& message) const;

    std::string
    decode(const std::string& message) const;

    dms::encoder::ENC_TYPE
    name(void) const;

  private:
    char encode(const char) const;
    char decode(const char) const;
};
