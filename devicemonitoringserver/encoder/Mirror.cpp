#include <encoder/Mirror.h>

string Mirror::encode(string input){

    string output;

    for (int i = input.size(); i >= 0; i--) {
        output = output.append(1, input[i]);

    }

    return output;

}

string Mirror::decode(string input){

    string output;

    for (int i = input.size(); i >= 0; i--) {
        output = output.append(1, input[i]);

    }

    return output;

}

string Mirror::getname() {

    return AlgorithmName;

}
