#ifndef MULTIPLY41_H
#define MULTIPLY41_H

#include <encoder/baseencoderexecutor.h>
class Multiply41 final: public BaseEncoderExecutor {

    public:

        string encode(const string& input) final;
        string decode(const string& input) final;
        string getname();
    private:
        string AlgorithmName = "Multiply41";
};



#endif // MULTIPLY41_H
