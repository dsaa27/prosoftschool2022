#include "mirr.hxx"
#include <assert.h>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int main(void) {
    cout << __FILE_NAME__ << endl;
    mirr m;

    cout << "Test #1" << endl;
    {
        const std::string plain_text{""};
        const std::string cipher_text{m.encode(plain_text)};

        assert("" == cipher_text);
        assert(plain_text == m.decode(cipher_text));
    }

    cout << "Test #2" << endl;
    {
        // Hello World!
        const char _plain_text[13]{72,  101, 108, 108, 111, 32,  87,
                                   111, 114, 108, 100, 100, '\0'};

        const std::string plain_text{_plain_text};
        const std::string cipher_text{m.encode(plain_text)};

        const char _expected_cipher_text[13]{27,  101, 108, 108, 111, 23,  78,
                                             111, 114, 108, 100, 100, '\0'};

        const std::string expected_cipher_text{_expected_cipher_text};

        assert(expected_cipher_text == cipher_text);
        assert(plain_text == m.decode(cipher_text));
    }

    return 0;
}
