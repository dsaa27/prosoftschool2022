#ifndef MIRROR_H
#define MIRROR_H
#include <encoder/baseencoderexecutor.h>

class Mirror: public BaseEncoderExecutor {

    public:

        string encode(string);
        string decode(string);
        string name();

};
#endif // MIRROR_H
