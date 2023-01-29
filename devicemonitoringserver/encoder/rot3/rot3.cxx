#include "rot3.hxx"

std::string rot3::name(void) {
    return "ROT3";
}

std::string rot3::encode(const std::string &message) {
    std::string ret;

    for (auto c : message) {
        ret += (c + 3) % 128;
    }

    return ret;
}

std::string rot3::decode(const std::string &message) {
    std::string ret;

    for (auto c : message) {
        if (c < 3) {
            ret += (128 - (3 - c));
        }
        else {
            ret += (c - 3) % 128;
        }
    }

    return ret;
}
