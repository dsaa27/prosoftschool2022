#include "messageencoder.h"


MessageEncoder::MessageEncoder()
{
    m_currentExecutor = nullptr;
    //TODO init m_executors
}

MessageEncoder::~MessageEncoder()
{
    for (const std::pair<std::string, BaseEncoderExecutor*>& value : m_executors)
        delete value.second;
}

bool MessageEncoder::encode(const std::string& originalMessage, std::string& encodedMessage) const
{
    if(!m_currentExecutor)
        return false;
    encodedMessage = m_currentExecutor->encode(originalMessage);
    return true;
}

bool MessageEncoder::decode(const std::string& encodedMessage, std::string& decodedMessage) const
{
    if(!m_currentExecutor)
        return false;
    decodedMessage = m_currentExecutor->decode(encodedMessage);
    return true;
}

bool MessageEncoder::setAlgorithm(const std::string& nameAlg)
{
    if (m_executors.find(nameAlg) == m_executors.end())
        return false;
    m_currentExecutor = m_executors.at(nameAlg);
    return true;
}

bool MessageEncoder::addAlgorithm(BaseEncoderExecutor* encoderExecutor)
{
    if (!encoderExecutor)
        return false;
    return m_executors.insert(std::make_pair(encoderExecutor->getName(), encoderExecutor)).second;
}

std::string MessageEncoder::getAlgName() const
{
    return m_currentExecutor->getName();
}

std::vector<std::string> MessageEncoder::getAllAlgNames() const
{
    std::vector<std::string> names;
    for (const std::pair<std::string, BaseEncoderExecutor*>& value : m_executors)
        names.push_back(value.first);
    return names;
}

