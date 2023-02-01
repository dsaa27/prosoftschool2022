#include "message_encoder.hxx"
#include "base_encoder.hxx"
#include "mul41/mul41.hxx"
#include "mirr/mirr.hxx"
#include "rot3/rot3.hxx"
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

int main(void) {
    cout << __FILE_NAME__ << endl;

    cout << "Test #1" << endl;
    {
        base_encoder* encoder{new rot3()};
        message_encoder message_encoder{encoder};

        std::string plain_text_in{"Hello world!"};
        std::string cipher_text{message_encoder.encode(plain_text_in)};

        std::string plain_text_out = message_encoder.decode(cipher_text);
        delete encoder;

        assert(plain_text_in == plain_text_out);
    }

    cout << "Test #2" << endl;
    {
        vector<base_encoder*> encoders{new rot3(), new mul41(), new mirr()};
        message_encoder message_encoder{};

        for (auto encoder : encoders) {
            message_encoder.register_encoder(encoder);
        }

        message_encoder.choose_encoder(encoders[1]->name());
        assert(message_encoder.curr_encoder_name() == "multiply41");

        std::string plain_text_in{"Hello world!"};
        std::string cipher_text{message_encoder.encode(plain_text_in)};

        std::string plain_text_out = message_encoder.decode(cipher_text);

        for (auto encoder : encoders) {
            delete encoder;
        }

        assert(plain_text_in == plain_text_out);
    }
}
