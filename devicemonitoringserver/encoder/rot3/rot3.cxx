#include "rot3.hxx"

std::string rot3::name(void) {
    return "ROT3";
}

char rot3::encode(const char c) {
    return (c + 3) % 128;
}

char rot3::decode(const char c) {
    if (3 <= c) {
        return (c - 3) % 128;
    }

    return (128 - (3 - c));
}

std::string rot3::encode(const std::string& message) {
    std::string ret;

    for (const char c : message) {
        ret += encode(c);
    }

    return ret;
}

std::string rot3::decode(const std::string& message) {
    std::string ret;

    for (const char c : message) {
        ret += decode(c);
    }

    return ret;
}
