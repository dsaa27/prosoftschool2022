#pragma once
#include <string>

// encoder
class base_encoder {
  public:
    virtual std::string encode(const std::string& message) const = 0;
    virtual std::string decode(const std::string& message) const = 0;
    virtual std::string name(void) const = 0;

    virtual ~base_encoder(void) = default;
};
