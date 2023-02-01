#include "mul41.hxx"
#include <string>

const std::string mul41::_name{"multiply41"};

std::string mul41::name(void) const {
    return _name;
}

std::string mul41::encode(const std::string& message) const {
    std::string ret;

    for (const char c : message) {
        const int16_t r{int16_t(c * 41)};

        if (r < 100) {
            // о двойке
            ret += 0x31;
        }

        else if (r >= 100 && r < 1000) {
            // о тройке
            ret += 0x23;
        }

        else if (r >= 1000) {
            // о четвёрке
            ret += 0x11;
        }

        ret += std::to_string(r);
    }

    return ret;
}

std::string mul41::decode(const std::string& message) const {
    std::string ret;
    int i = 0;

    while (i < message.length()) {
        if (message[i] == 0x31) {
            const int num{(message[i + 1] - '0') * 10 + (message[i + 2] - '0')};
            ret += num / 41;
            i += 3;
        }

        else if (message[i] == 0x23) {
            const int num{(message[i + 1] - '0') * 100 +
                          (message[i + 2] - '0') * 10 + (message[i + 3] - '0')};
            ret += num / 41;
            i += 4;
        }

        else if (message[i] == 0x11) {
            const int num{(message[i + 1] - '0') * 1000 +
                          (message[i + 2] - '0') * 100 +
                          (message[i + 3] - '0') * 10 + (message[i + 4] - '0')};
            ret += num / 41;
            i += 5;
        }

        else {
            ret += '\0';
            i++;
        }
    }

    return ret;
}
