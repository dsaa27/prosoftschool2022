#include "MessageEncoder.h"

MessageEncoder::~MessageEncoder()
{
    for (const std::pair<std::string, BaseEncoderExecutor*> &pair : m_allAlgorithms)
        delete pair.second;
}

bool MessageEncoder::addAlgorithm(BaseEncoderExecutor *algorithm)
{
    if (!algorithm)
        return false;
    m_allAlgorithms.insert(std::make_pair(algorithm->getName(), algorithm));
    return true;
}

bool MessageEncoder::chooseAlgorithm(const std::string& algorithm)
{
    if (m_allAlgorithms.find(algorithm) != m_allAlgorithms.end())
    {
        m_currentAlgorithm = m_allAlgorithms[algorithm];
        return true;
    }
    return false;
}

std::optional<std::string> MessageEncoder::decode(const std::string &message)
{
    if (m_currentAlgorithm)
        return { m_currentAlgorithm->decode(message) };
    else
        return std::nullopt;
}

std::optional<std::string> MessageEncoder::encode(const std::string &message)
{
    if (m_currentAlgorithm)
        return { m_currentAlgorithm->encode(message) };
    else
        return std::nullopt;
}

std::vector<std::string> MessageEncoder::getAvailableAlgorithms() {
    std::vector<std::string> allAlgsName = {};
    for (const std::pair<std::string, BaseEncoderExecutor*> &alg : m_allAlgorithms)
    {
        allAlgsName.push_back(alg.first);
    }
    return allAlgsName;
}

