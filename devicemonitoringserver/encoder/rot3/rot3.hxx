#pragma once
#include "../base_encoder.hxx"

class rot3 : public base_encoder {
  private:
    static const std::string _name;

  public:
    std::string encode(const std::string& message) const;
    std::string decode(const std::string& message) const;
    std::string name(void) const;

  private:
    char encode(const char c) const;
    char decode(const char c) const;
};
