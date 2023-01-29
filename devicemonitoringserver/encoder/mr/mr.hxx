#pragma once
#include "../base_encoder.hxx"

class mr : public base_encoder {
  public:
    std::string encode(const std::string& message);
    std::string decode(const std::string& message);
    std::string name(void);

  private:
    char encode(const char);
    char decode(const char);
};
