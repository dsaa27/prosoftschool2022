#pragma once
#include "../base_encoder.hxx"

class rot3 : public base_encoder {
  public:
    std::string encode(const std::string& message);
    std::string decode(const std::string& message);
    std::string name(void);

  private:
    char encode(const char c);
    char decode(const char c);
};
