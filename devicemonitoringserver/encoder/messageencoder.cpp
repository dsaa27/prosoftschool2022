#include "messageencoder.h"
#include <iostream>

void MessageEncoder::setEncodeAlgorithm (const std::string& algoName)
{
    if (!m_algoNameMap.contains(algoName))
    {
        std::cerr << "The encoding algorithm '" << algoName << "' doesn't exist" << std::endl;
        return;
    }
    m_Algorithm = m_algoNameMap[algoName];
}

std::string MessageEncoder::encode(const std::string& message)
{
    return m_Algorithm->encode(message);
}

std::string MessageEncoder::decode(const std::string& message)
{
    return m_Algorithm->decode(message);
}

std::string MessageEncoder::name()
{
    return m_Algorithm->name();
}

void MessageEncoder::registerNewAlgorithm(BaseEncoderExecutor& newAlgorithm)
{
    std::string newAlgorithmName = newAlgorithm.name();
    if (m_algoNameMap.contains(newAlgorithmName))
    {
        std::cerr << "The encoding algorithm '" << newAlgorithmName << "' already exist" << std::endl;
        return;
    }
    std::string name = newAlgorithm.name();
    m_algoNameMap[name] = &newAlgorithm;
}

