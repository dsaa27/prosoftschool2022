#pragma once
#include "../base_encoder.hxx"

class mirr : public base_encoder {
  private:
    static const std::string _name;

  public:
    std::string encode(const std::string& message) const;
    std::string decode(const std::string& message) const;
    std::string name(void) const;

  private:
    char encode(const char) const;
    char decode(const char) const;
};
