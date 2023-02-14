#ifndef MULTIPLY41_H
#define MULTIPLY41_H

#include <encoder/baseencoderexecutor.h>
class Multiply41 : public BaseEncoderExecutor {

    public:

        string encode(string);
        string decode(string);
        string getname();
    private:
        string AlgorithmName = "Multiply41";
};



#endif // MULTIPLY41_H
