#include "message_encoder.hxx"
#include <cassert>
#include <iostream>
using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Метод кодировки по умолчанию" << endl;

        const message_encoder enc{};
        assert("mirror" == enc.curr_encoder());
    }

    {
        cout << "Инициализация с разными методами кодировки" << endl;

        {
            const message_encoder enc(ENC_TYPE::MIRR);
            assert("mirror" == enc.curr_encoder());
        }

        {
            const message_encoder enc(ENC_TYPE::MUL41);
            assert("multiply41" == enc.curr_encoder());
        }

        {
            const message_encoder enc(ENC_TYPE::ROT3);
            assert("rot3" == enc.curr_encoder());
        }
    }

    {
        cout << "Изменение текущего метода кодировки" << endl;

        message_encoder enc(ENC_TYPE::ROT3);
        assert("rot3" == enc.curr_encoder());

        enc.set_encoder(ENC_TYPE::MUL41);
        assert("multiply41" == enc.curr_encoder());
    }

    {
        cout << "rot3" << endl;

        const string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                   "MNOPQRSTUVWXYZ1234567890.,!@#$%^&*(){}"};

        const message_encoder enc(ENC_TYPE::ROT3);
        assert("rot3" == enc.curr_encoder());

        const std::string cipher_text{enc.encode(plain_text_in)};
        const std::string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }

    {
        cout << "multiply41" << endl;

        const string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                   "MNOPQRSTUVWXYZ1234567890.,!@#$%^&*(){}"};

        const message_encoder enc(ENC_TYPE::MUL41);
        assert("multiply41" == enc.curr_encoder());

        const std::string cipher_text{enc.encode(plain_text_in)};
        const std::string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }

    {
        cout << "mirror" << endl;

        const string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                   "MNOPQRSTUVWXYZ1234567890.,!@#$%^&*(){}"};

        const message_encoder enc(ENC_TYPE::MIRR);
        assert("mirror" == enc.curr_encoder());

        const string cipher_text{enc.encode(plain_text_in)};
        const string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }
}
