#pragma once
#include "base_encoder.hxx"
#include <map>
#include <memory>
#include <string>

class message_encoder {
  private:
    std::map<dms::encoder::ENC_TYPE,
             std::shared_ptr<const dms::encoder::base_encoder>>
        _encoder_table;

    std::shared_ptr<const dms::encoder::base_encoder> _curr;

  public:
    void
    set_encoder(const dms::encoder::ENC_TYPE type);

    std::string
    encode(const std::string&) const;

    std::string
    decode(const std::string&) const;

    dms::encoder::ENC_TYPE
    curr_encoder(void) const;

    message_encoder(void);
    message_encoder(dms::encoder::ENC_TYPE);
};
