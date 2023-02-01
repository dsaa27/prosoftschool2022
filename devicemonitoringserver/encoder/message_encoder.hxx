#pragma once
#include <map>
#include <string>
#include "base_encoder.hxx"

class message_encoder {
  private:
    std::map<const std::string, base_encoder*> encoder_table;
    const base_encoder* main_encoder;

  public:
    void choose_encoder(const std::string& name);
    void register_encoder(base_encoder*);

    std::string encode(const std::string&) const;
    std::string decode(const std::string&) const;

    std::string curr_encoder_name(void) const;

    message_encoder(base_encoder*);
    message_encoder(void) = default;
};
