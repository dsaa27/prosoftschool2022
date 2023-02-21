#include "mirr.hxx"
#include <string>

dms::encoder::ENC_TYPE
dms::encoder::mirr::name(void) const {
    return dms::encoder::ENC_TYPE::MIRR;
}

char
dms::encoder::mirr::encode(const char c) const {
    if (100 <= c) {
        return c;
    }

    const char low{char(c % 10)};
    const char high{char(c / 10)};

    return (low * 10 + high);
}

char
dms::encoder::mirr::decode(const char c) const {
    return encode(c);
}

std::string
dms::encoder::mirr::encode(const std::string& message) const {
    std::string ret{};

    for (const char c : message) {
        ret += encode(c);
    }

    return ret;
}

std::string
dms::encoder::mirr::decode(const std::string& message) const {
    return mirr::encode(message);
}
