#include "base_encoder.hxx"
#include "message_encoder.hxx"
#include <cassert>
#include <iostream>

using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Метод кодировки по умолчанию" << endl;

        const dms::encoding::message_encoder menc{};
        assert(dms::encoder::ENC_TYPE::MIRR == menc.curr_encoder());
    }

    {
        cout << "Инициализация с разными методами кодировки" << endl;

        {
            const dms::encoding::message_encoder menc{
                dms::encoder::ENC_TYPE::MIRR};
            assert(dms::encoder::ENC_TYPE::MIRR == menc.curr_encoder());
        }

        {
            const dms::encoding::message_encoder menc{
                dms::encoder::ENC_TYPE::MUL41};
            assert(dms::encoder::ENC_TYPE::MUL41 == menc.curr_encoder());
        }

        {
            const dms::encoding::message_encoder menc{
                dms::encoder::ENC_TYPE::ROT3};
            assert(dms::encoder::ENC_TYPE::ROT3 == menc.curr_encoder());
        }
    }

    {
        cout << "Изменение текущего метода кодировки" << endl;

        dms::encoding::message_encoder menc{dms::encoder::ENC_TYPE::ROT3};
        assert(dms::encoder::ENC_TYPE::ROT3 == menc.curr_encoder());

        menc.set_encoder(dms::encoder::ENC_TYPE::MUL41);
        assert(dms::encoder::ENC_TYPE::MUL41 == menc.curr_encoder());
    }

    {
        cout << "rot3" << endl;

        const string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                   "MNOPQRSTUVWXYZ1234567890.,!@#$%^&*(){}"};

        const dms::encoding::message_encoder enc{dms::encoder::ENC_TYPE::ROT3};
        assert(dms::encoder::ENC_TYPE::ROT3 == enc.curr_encoder());

        const string cipher_text{enc.encode(plain_text_in)};
        const string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }

    {
        cout << "multiply41" << endl;

        const string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                   "MNOPQRSTUVWXYZ1234567890.,!@#$%^&*(){}"};

        const dms::encoding::message_encoder enc{dms::encoder::ENC_TYPE::MUL41};
        assert(dms::encoder::ENC_TYPE::MUL41 == enc.curr_encoder());

        const std::string cipher_text{enc.encode(plain_text_in)};
        const std::string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }

    {
        cout << "mirror" << endl;

        const string plain_text_in{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                   "MNOPQRSTUVWXYZ1234567890.,!@#$%^&*(){}"};

        const dms::encoding::message_encoder enc{dms::encoder::ENC_TYPE::MIRR};
        assert(dms::encoder::ENC_TYPE::MIRR == enc.curr_encoder());

        const string cipher_text{enc.encode(plain_text_in)};
        const string plain_text_out{enc.decode(cipher_text)};

        assert(plain_text_in == plain_text_out);
    }
}
