#include "messageencoder.h"

#include "mirror.h"
#include "multiply41.h"
#include "rot3.h"


MessageEncoder::MessageEncoder()
{
    m_currentExecutor = nullptr;
    Mirror* mirrorExec = new Mirror();
    Multiply41* multiply41Exec = new Multiply41();
    ROT3* rot3Exec = new ROT3();
    m_executors =
    {
        {mirrorExec->getName(), mirrorExec},
        {multiply41Exec->getName(), multiply41Exec},
        {rot3Exec->getName(), rot3Exec}
    };
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

bool MessageEncoder::setAlgorithm(const std::string& algName)
{
    if (m_executors.find(algName) == m_executors.end())
        return false;
    m_currentExecutor = m_executors.at(algName);
    return true;
}

bool MessageEncoder::addAlgorithm(BaseEncoderExecutor* encoderExecutor)
{
    if (!encoderExecutor)
        return false;
    return m_executors.insert(std::make_pair(encoderExecutor->getName(), encoderExecutor)).second;
}

bool MessageEncoder::getAlgName(std::string& algName) const
{
    if(!m_currentExecutor)
        return false;
    algName = m_currentExecutor->getName();
    return true;
}

std::vector<std::string> MessageEncoder::getAllAlgNames() const
{
    std::vector<std::string> names;
    for (const std::pair<std::string, BaseEncoderExecutor*>& value : m_executors)
        names.push_back(value.first);
    return names;
}

