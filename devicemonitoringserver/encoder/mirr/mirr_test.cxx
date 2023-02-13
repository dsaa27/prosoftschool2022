#include "mirr.hxx"
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Имя кодировщика" << endl;
        const dms::encoder::mirr mirr{};

        assert(dms::encoder::ENC_TYPE::MIRR == mirr.name());
    }

    {
        cout << "Пустое сообщение" << endl;
        const dms::encoder::mirr mirr{};

        const string plain_text{};
        const string cipher_text{mirr.encode(plain_text)};

        assert("" == cipher_text);
        assert(plain_text == mirr.decode(cipher_text));
    }

    {
        cout << "Hello world!" << endl;
        const dms::encoder::mirr mirr{};

        // Hello World!
        const char _plain_text[13]{72,  101, 108, 108, 111, 32,  87,
                                   111, 114, 108, 100, 33,  '\0'};

        const string plain_text{_plain_text};
        const string cipher_text{mirr.encode(plain_text)};

        const char _expected_cipher_text[13]{27,  101, 108, 108, 111, 23,  78,
                                             111, 114, 108, 100, 33,  '\0'};

        const string expected_cipher_text{_expected_cipher_text};

        assert(expected_cipher_text == cipher_text);
        assert(plain_text == mirr.decode(cipher_text));
    }

    return 0;
}
