#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H
#include "baseencoderexecutor.h"
#include "rot3.h"
#include "mirror.h"
#include "multiply41.h"
#include <string>
#include <map>
#include <vector>

//модуль шифрования
class MessageEncoder : public BaseEncoderExecutor
{
public:
    std::string encode (std::string message) final;
    std::string decode (std::string message) final;
    std::string name() final;
    void setEncodeAlgorithm (std::string algoName);
    void registerNewAlgorithm (BaseEncoderExecutor& newAlgorithm);

private:
    Rot3 m_rot3;
    Mirror m_mirror;
    Multiply41 m_multiply41;
    std::string m_algoName = "ROT3";
    std::map <std::string, BaseEncoderExecutor*> m_algoNameMap = {{"ROT3", &m_rot3},
                                                                  {"Mirror", &m_mirror},
                                                                  {"Multiply41", &m_multiply41}};
};
#endif // MESSAGEENCODER_H
