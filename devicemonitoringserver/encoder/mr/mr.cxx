#include "mr.hxx"
#include <string>

std::string mr::name(void) {
    return "mirror";
}

char mr::encode(const char c) {
    if (100 <= c) {
        return c;
    }

    const char low{char(c % 10)};
    const char high{char(c / 10)};

    return (low * 10 + high);
}

char mr::decode(const char c) {
    return encode(c);
}

std::string mr::encode(const std::string& message) {
    std::string ret;

    for (const char c : message) {
        ret += encode(c);
    }

    return ret;
}

std::string mr::decode(const std::string &message) {
    return mr::encode(message);
}
