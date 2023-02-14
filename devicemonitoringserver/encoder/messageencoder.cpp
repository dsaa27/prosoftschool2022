#include "messageencoder.h"
#include <iostream>

void MessageEncoder::setEncodeAlgorithm (const std::string& algoName)
{
    if (m_algoNameMap.find(algoName) == m_algoNameMap.end())
    {
        std::cerr << "The encoding algorithm '" << algoName << "' doesn't exist" << std::endl;
        return;
    }
    m_algoName = algoName;
}

std::string MessageEncoder::encode(const std::string& message)
{
    return m_algoNameMap[m_algoName]->encode(message);
}

std::string MessageEncoder::decode(const std::string& message)
{
    return m_algoNameMap[m_algoName]->decode(message);;
}

std::string MessageEncoder::name()
{
    return m_algoName;
}

void MessageEncoder::registerNewAlgorithm(BaseEncoderExecutor& newAlgorithm)
{
    std::string newAlgorithmName = newAlgorithm.name();
    if (m_algoNameMap.find(newAlgorithmName) != m_algoNameMap.end())
    {
        std::cerr << "The encoding algorithm '" << newAlgorithmName << "' already exist" << std::endl;
        return;
    }
    std::string name = newAlgorithm.name();
    m_algoNameMap[name] = &newAlgorithm;
}

