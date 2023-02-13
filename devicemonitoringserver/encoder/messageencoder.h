#include <encoder/baseencoderexecutor.h>
#include <string>
#include <map>
#include <encoder/ROT3.h>
#include <encoder/Mirror.h>
#include <encoder/Multiply41.h>

class MessageEncoder : public BaseEncoderExecutor {

    public:
        string encode (string message);
        string decode (string message);
        string name();

        void SetEncodeAlgorithm (string NameOfAlgorithm);

        void NewAlgorithm (BaseEncoderExecutor & newAlgorithm);
    private:
        ROT3 rot3;
        Mirror mirror;
        Multiply41 multiply41;
        string NameOfAlgorithm_m = "ROT3";
        std::map <string, BaseEncoderExecutor*> NameOfAlgorithmMap = {{"ROT3", &rot3}, /*{"Mirror", &mirror},*/ {"Multiply41", &multiply41}};

};




