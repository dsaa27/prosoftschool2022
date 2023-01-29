#include "rot3.hxx"
#include <assert.h>
#include <iostream>
using namespace std;

int main(void) {
    cout << __FILE_NAME__ << endl;
    rot3 r;

    cout << "Test #1" << endl;
    {
        const std::string plain_text{""};
        const std::string cipher_text{r.encode(plain_text)};

        assert("" == cipher_text);
        assert(plain_text == r.decode(cipher_text));
    }

    cout << "Test #2" << endl;
    {
        const std::string plain_text{"Hello World!"};
        const std::string cipher_text{r.encode(plain_text)};

        assert("Khoor#Zruog$" == cipher_text);
        assert(plain_text == r.decode(cipher_text));
    }

    cout << "Test #3" << endl;
    {
        const std::string plain_text{"I love you CXX(C++)."};
        const std::string cipher_text{r.encode(plain_text)};

        assert("L#oryh#|rx#F[[+F..,1" == cipher_text);
        assert(plain_text == r.decode(cipher_text));
    }

    return 0;
}
