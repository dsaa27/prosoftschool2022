#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

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
        string getname();

        void SetEncodeAlgorithm (string NameOfAlgorithm);
        void NewAlgorithm (BaseEncoderExecutor & newAlgorithm);

    private:
        ROT3 rot3;
        Mirror mirror;
        Multiply41 multiply41;
        string SelectedAlgorithm;
        std::map <string, BaseEncoderExecutor*> AlgorithmMap = {{"ROT3", &rot3}, {"Mirror", &mirror}, {"Multiply41", &multiply41}};

};

#endif // MESSAGEENCODER_H


