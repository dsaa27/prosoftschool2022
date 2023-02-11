#include "message_encoder.hxx"
#include <cassert>
#include <iostream>
using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Test #1" << endl;

        message_encoder enc;
        assert("mirror" == enc.curr_encoder());
    }

    {
        cout << "Test #2" << endl;

        {
            message_encoder enc(ENC_TYPE::MIRR);
            assert("mirror" == enc.curr_encoder());
        }

        {
            message_encoder enc(ENC_TYPE::MUL41);
            assert("multiply41" == enc.curr_encoder());
        }

        {
            message_encoder enc(ENC_TYPE::ROT3);
            assert("rot3" == enc.curr_encoder());
        }
    }

    {
        cout << "Test #3" << endl;

        message_encoder enc(ENC_TYPE::ROT3);
        enc.set_encoder(ENC_TYPE::MUL41);

        assert("multiply41" == enc.curr_encoder());
    }

    {
        cout << "Test #4" << endl;

        const std::string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                        "MNOPQRSTUVWXYZ1234567890!@#$%^&*()"};

        message_encoder enc(ENC_TYPE::ROT3);

        const std::string cipher_text{enc.encode(plain_text_in)};
        const std::string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }

    {
        cout << "Test #5" << endl;

        const std::string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                        "MNOPQRSTUVWXYZ1234567890!@#$%^&*()"};

        message_encoder enc(ENC_TYPE::MUL41);

        const std::string cipher_text{enc.encode(plain_text_in)};
        const std::string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }

    {
        cout << "Test #6" << endl;

        const std::string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                        "MNOPQRSTUVWXYZ1234567890!@#$%^&*()"};

        message_encoder enc(ENC_TYPE::MIRR);

        const std::string cipher_text{enc.encode(plain_text_in)};
        const std::string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }
}
