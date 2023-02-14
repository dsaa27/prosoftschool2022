#ifndef ROT3_H
#define ROT3_H

#include <encoder/baseencoderexecutor.h>

class ROT3 : public BaseEncoderExecutor {

    public:

        string encode(string);
        string decode(string);
        string getname();
    private:
        string AlgorithmName = "ROT3";
};

#endif // ROT3_H
