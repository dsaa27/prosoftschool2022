#pragma once
#include "base_encoder.hxx"
#include <map>
#include <memory>
#include <string>

enum class ENC_TYPE : std::uint8_t { MIRR = 0u, MUL41, ROT3 };

class message_encoder {
  private:
    std::map<ENC_TYPE, std::shared_ptr<const base_encoder>> _encoder_table;
    std::shared_ptr<const base_encoder> _curr;

  public:
    void
    set_encoder(const ENC_TYPE type);

    std::string
    encode(const std::string&) const;

    std::string
    decode(const std::string&) const;

    // временно string, ENC_TYPE нужен
    std::string
    curr_encoder(void) const;

    message_encoder(void);
    message_encoder(ENC_TYPE);
};
