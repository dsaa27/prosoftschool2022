#include "rot3.hxx"
#include <cassert>
#include <iostream>
using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Empty message" << endl;
        const dms::encoder::rot3 rot3{};

        assert(dms::encoder::ENC_TYPE::ROT3 == rot3.name());

        const string plain_text{};
        const string cipher_text{rot3.encode(plain_text)};

        assert(cipher_text.empty());
        assert(rot3.decode(cipher_text).empty());
    }

    {
        cout << "Hello World!" << endl;
        const dms::encoder::rot3 rot3{};

        const string plain_text_in{"Hello World!"};
        const string expected_cipher_text{"Khoor#Zruog$"};

        const string cipher_text{rot3.encode(plain_text_in)};
        const string plain_text_out{rot3.decode(cipher_text)};

        assert(expected_cipher_text == cipher_text);
        assert(plain_text_in == plain_text_out);
    }

    {
        cout << "I love you CXX(C++)." << endl;
        const dms::encoder::rot3 rot3{};

        const string plain_text_in{"I love you CXX(C++)."};
        const string expected_cipher_text{"L#oryh#|rx#F[[+F..,1"};

        const string cipher_text{rot3.encode(plain_text_in)};
        const string plain_text_out{rot3.decode(cipher_text)};

        assert(expected_cipher_text == cipher_text);
        assert(plain_text_in == plain_text_out);
    }
}
