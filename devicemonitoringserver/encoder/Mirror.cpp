#include <encoder/Mirror.h>

string Mirror::encode(const string& input){

    string output;

    for (int i = input.size(); i >= 0; --i) {
        output = output.append(1, input[i]);

    }
    return output;
}

string Mirror::decode(const string& input){

    return encode(input);
}

string Mirror::getname() {

    return AlgorithmName;

}
