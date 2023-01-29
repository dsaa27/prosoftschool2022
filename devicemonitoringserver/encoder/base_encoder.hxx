#pragma once
#include <string>

class base_encoder {
  public:
    virtual std::string encode(const std::string& message) = 0;
    virtual std::string decode(const std::string& message) = 0;
    virtual std::string name(void) = 0;
};
