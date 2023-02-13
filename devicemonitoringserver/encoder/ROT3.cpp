#include <encoder/ROT3.h>

string ROT3::encode(string input){

    string output;

    for (unsigned i = 0; i < input.size(); i++) {

        if ((int)input[i] >= 256) {

            output += input[i] - 253;

        } else output += input[i] + 3;
    }


    return output;
}

string ROT3::decode(string input) {

    string output;
    int buffer;

    for (unsigned int i = 0; i < input.size(); i++) {

        if ((int)input[i] <= 3) {
            output += 256 - input[i];
        } else output += input[i] - 3;
    }

    return output;
}
