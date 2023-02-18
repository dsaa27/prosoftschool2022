#ifndef ROT3_H
#define ROT3_H

#include <encoder/baseencoderexecutor.h>

class ROT3 final: public BaseEncoderExecutor {

    public:

        string encode(const string& input) final;
        string decode(const string& input) final;
        string getname();
    private:
        string AlgorithmName = "ROT3";
};

#endif // ROT3_H
