#include "mul41.hxx"
#include <cstdint>
#include <string>

#include <iostream>
using namespace std;

enum class VALUE_INDICATOR : char { DYAD = 0x31, TRIO = 0x23, QUAD = 0x11 };

dms::encoder::ENC_TYPE
dms::encoder::mul41::name(void) const {
    return dms::encoder::ENC_TYPE::MUL41;
}

std::string
dms::encoder::mul41::encode(const std::string& message) const {
    std::string ret{};

    for (const char c : message) {
        const std::uint16_t r{static_cast<std::uint16_t>(41 * c)};

        // Однозначное число может получиться только если символ '\0'
        // Для него индикатор не вводится

        if (r < 100u && 0u != r) {
            ret += static_cast<const char>(VALUE_INDICATOR::DYAD);
        }

        else if (r >= 100u && r < 1000u) {
            ret += static_cast<const char>(VALUE_INDICATOR::TRIO);
        }

        else if (r >= 1000u) {
            ret += static_cast<const char>(VALUE_INDICATOR::QUAD);
        }

        ret += std::to_string(r);
    }

    return ret;
}

std::string
dms::encoder::mul41::decode(const std::string& message) const {
    std::string ret{};
    int i = 0;

    while (i < message.length()) {
        if (message[i] == static_cast<const char>(VALUE_INDICATOR::DYAD)) {
            const int num{(message[i + 1] - '0') * 10 + (message[i + 2] - '0')};
            ret += num / 41;
            i += 3;
        }

        else if (message[i] == static_cast<const char>(VALUE_INDICATOR::TRIO)) {
            const int num{(message[i + 1] - '0') * 100 +
                          (message[i + 2] - '0') * 10 + (message[i + 3] - '0')};
            ret += num / 41;
            i += 4;
        }

        else if (message[i] == static_cast<const char>(VALUE_INDICATOR::QUAD)) {
            const int num{(message[i + 1] - '0') * 1000 +
                          (message[i + 2] - '0') * 100 +
                          (message[i + 3] - '0') * 10 + (message[i + 4] - '0')};
            ret += num / 41;
            i += 5;
        }

        else {
            // встретился нуль символ
            // 0 * 441 = 0
            ret += '\0';
            i++;
        }
    }

    return ret;
}
