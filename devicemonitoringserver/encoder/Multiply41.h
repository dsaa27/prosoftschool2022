#ifndef MULTIPLY41_H
#define MULTIPLY41_H

#include <encoder/baseencoderexecutor.h>
class Multiply41 : public BaseEncoderExecutor {

    public:

        string encode(string);
        string decode(string);
        string name();

};



#endif // MULTIPLY41_H
