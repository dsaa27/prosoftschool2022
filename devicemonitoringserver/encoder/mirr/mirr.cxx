#include "mirr.hxx"
#include <string>

const std::string mirr::_name{"mirror"};

std::string mirr::name(void) const {
    return _name;
}

char mirr::encode(const char c) const {
    if (100 <= c) {
        return c;
    }

    const char low{char(c % 10)};
    const char high{char(c / 10)};

    return (low * 10 + high);
}

char mirr::decode(const char c) const {
    return encode(c);
}

std::string mirr::encode(const std::string& message) const {
    std::string ret;

    for (const char c : message) {
        ret += encode(c);
    }

    return ret;
}

std::string mirr::decode(const std::string &message) const {
    return mirr::encode(message);
}
