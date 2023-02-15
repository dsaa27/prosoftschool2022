#pragma once
#include "../base_encoder.hxx"

namespace dms {
    namespace encoder {
        class rot3;
    }
}

class dms::encoder::rot3 : public dms::encoder::base_encoder {
  public:
    std::string encode(const std::string& message) const;
    std::string decode(const std::string& message) const;
    dms::encoder::ENC_TYPE name(void) const;

  private:
    char encode(const char c) const;
    char decode(const char c) const;
};
