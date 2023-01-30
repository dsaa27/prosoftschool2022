#include "mul41.hxx"
#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

int main(void) {
    cout << __FILE_NAME__ << endl;
    mul41 m;

    cout << "Test #1" << endl;
    {
        // Fender
        const char _plain_text[]{70, 101, 110, 100, 101, 114, 0};
        const string plain_text{_plain_text};

        const char _expected_cipher_text[]{
            0x11, '2', '8', '7', '0',
            0x11, '4', '1', '4', '1',
            0x11, '4', '5', '1', '0',
            0x11, '4', '1', '0', '0',
            0x11, '4', '1', '4', '1',
            0x11, '4', '6', '7', '4'
        };

        const std::string expected_cipher_text{_expected_cipher_text};
        const string cipher_text{m.encode(plain_text)};

        assert(cipher_text == expected_cipher_text);
        assert(plain_text == m.decode(cipher_text));
    }

    cout << "Test #2" << endl;
    {
        const char _plain_text[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        const string plain_text{_plain_text};

        const char _expected_cipher_text[]{
            0x31, '4', '1',
            0x31, '8', '2',
            0x23, '1', '2', '3',
            0x23, '1', '6', '4',
            0x23, '2', '0', '5',
            0x23, '2', '4', '6',
            0x23, '2', '8', '7',
            0x23, '3', '2', '8',
            0x23, '3', '6', '9',
            0x23, '4', '1', '0',
            0x23, '3', '6', '9',
            0x23, '3', '2', '8',
            0x23, '2', '8', '7',
            0x23, '2', '4', '6',
            0x23, '2', '0', '5',
            0x23, '1', '6', '4',
            0x23, '1', '2', '3',
            0x31, '8', '2',
            0x31, '4', '1',
            0
        };

        const std::string expected_cipher_text{_expected_cipher_text};
        const std::string cipher_text{m.encode(plain_text)};

        assert(cipher_text == expected_cipher_text);
        assert(plain_text == m.decode(cipher_text));
    }

    return 0;
}
