#include <encoder/Multiply41.h>

string Multiply41::encode(const string& input) {

    string output;
    int buffer;

    for (unsigned int i = 0; i < input.size(); ++i) {

        buffer = input[i] * 41;
        int prev = buffer / 100;
        int next = buffer % 100;

        output += prev;
        output += next;

    }
    return output;
}

string Multiply41::decode(const string& input) {

    string output;
    int buffer = 0;
    unsigned int size = input.size();
    for (unsigned int i = 0; i < size; i += 2) {
        buffer = input[i] * 100 + input[i+1];
        output += buffer / 41;
    }
    return output;
}

string Multiply41::getname() {

    return AlgorithmName;

}
