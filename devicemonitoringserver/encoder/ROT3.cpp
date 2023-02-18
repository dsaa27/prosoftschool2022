#include <encoder/ROT3.h>

string ROT3::encode(const string& input){

    string output;

    for (unsigned i = 0; i < input.size(); ++i) {

        if ((int)input[i] >= 256) {
            int buf = 3 - 256;
            output += input[i] + buf;

        } else output += input[i] + 3;
    }


    return output;
}

string ROT3::decode(const string& input) {

    string output;

    for (unsigned int i = 0; i < input.size(); ++i) {

        if ((int)input[i] <= 3) {
            output += 256 - input[i];
        } else output += input[i] - 3;
    }

    return output;
}


string ROT3::getname() {

    return AlgorithmName;

}
