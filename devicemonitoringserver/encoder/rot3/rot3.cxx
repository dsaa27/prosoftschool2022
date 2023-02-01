#include "rot3.hxx"

const std::string rot3::_name{"rot3"};

std::string rot3::name(void) const {
    return _name;
}

char rot3::encode(const char c) const {
    return (c + 3) % 128;
}

char rot3::decode(const char c) const {
    if (3 <= c) {
        return (c - 3) % 128;
    }

    return (128 - (3 - c));
}

std::string rot3::encode(const std::string& message) const {
    std::string ret;

    for (const char c : message) {
        ret += encode(c);
    }

    return ret;
}

std::string rot3::decode(const std::string& message) const {
    std::string ret;

    for (const char c : message) {
        ret += decode(c);
    }

    return ret;
}
