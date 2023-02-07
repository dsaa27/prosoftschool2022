#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H
#include "baseencoderexecutor.h"
#include "rot3.h"
#include "mirror.h"
#include "multiply41.h"
#include <string>
#include <map>
#include <vector>

class MessageEncoder : public BaseEncoderExecutor
{
public:
    /*!
     * \brief Зашифровать строку.
     */
    std::string encode (std::string message) final;
    /*!
     * \brief Расшифровать строку.
     */
    std::string decode (std::string message) final;
    /*!
     * \brief Получить название текущего алгоритма шифрования.
     */
    std::string name() final;
    /*!
     * \brief Выбрать алгоритм шифрования по его названию.
     */
    void setEncodeAlgorithm (std::string algoName);
    /*!
     * \brief Добавить новый алгоритм шифрования (без его установки в качестве текущего).
     */
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
