#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H
#include "baseencoderexecutor.h"
#include "rotX.h"
#include "mirror.h"
#include "multiply41.h"
#include <string>
#include <map>
#include <vector>

class MessageEncoder final : public BaseEncoderExecutor
{
public:
    //BaseEncoderExecutor interface
    std::string encode (const std::string &message) final;
    std::string decode (const std::string &message) final;
    std::string name() final;
    /*!
     * \brief Выбрать алгоритм шифрования по его названию.
     */
    void setEncodeAlgorithm (const std::string &algoName);
    /*!
     * \brief Добавить новый алгоритм шифрования (без его установки в качестве текущего).
     */
    void registerNewAlgorithm (BaseEncoderExecutor& newAlgorithm);

private:
    //Rot3 m_rot3;
    RotX m_rot3{3};
    Mirror m_mirror;
    Multiply41 m_multiply41;
    std::string m_algoName = m_rot3.name();
    std::map <std::string, BaseEncoderExecutor*> m_algoNameMap = {{"ROT3", &m_rot3},
                                                                  {"Mirror", &m_mirror},
                                                                  {"Multiply41", &m_multiply41}};
};
#endif // MESSAGEENCODER_H
