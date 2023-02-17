#include "rot3.hxx"

dms::encoder::ENC_TYPE
dms::encoder::rot3::name(void) const {
    return dms::encoder::ENC_TYPE::ROT3;
}

char
dms::encoder::rot3::encode(const char c) const {
    return (c + 3) % 128;
}

char
dms::encoder::rot3::decode(const char c) const {
    if (3 <= c) {
        return (c - 3) % 128;
    }

    return (128 - (3 - c));
}

std::string
dms::encoder::rot3::encode(const std::string& message) const {
    std::string ret{};

    for (const char c : message) {
        ret += encode(c);
    }

    return ret;
}

std::string
dms::encoder::rot3::decode(const std::string& message) const {
    std::string ret{};

    for (const char c : message) {
        ret += decode(c);
    }

    return ret;
}
