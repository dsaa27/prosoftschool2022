#ifndef MIRROR_H
#define MIRROR_H
#include <encoder/baseencoderexecutor.h>

class Mirror final: public BaseEncoderExecutor{

    public:

        string encode(const string& input) final;
        string decode(const string& input) final;
        string getname();
    private:
        string AlgorithmName = "Mirror";


};
#endif // MIRROR_H
