#include "mr.hxx"
#include <assert.h>
#include <cstring>
#include <string>

int main(void) {
    mr m;

    {
        const std::string plain_text{""};
        const std::string cipher_text{m.encode(plain_text)};

        assert("" == cipher_text);
        assert(plain_text == m.decode(cipher_text));
    }

    {
        // Hello World!
        const char plain_text[13]{72,  101, 108, 108, 111, 32, 87,
                                  111, 114, 108, 100, 100, 0};

        const std::string cipher_text{m.encode(std::string{plain_text})};

        const char expected_cipher_text[13]{27,  101, 108, 108, 111, 23, 78,
                                            111, 114, 108, 100, 100, 0};

        assert(0 == std::strcmp(cipher_text.c_str(), expected_cipher_text));
        assert(std::string{plain_text} == m.decode(cipher_text));
    }

    return 0;
}
