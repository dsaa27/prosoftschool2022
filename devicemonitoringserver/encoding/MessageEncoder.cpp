#include "MessageEncoder.h"
#include "ROT3.h"
#include "Mirror.h"
#include "Multiply41.h"

MessageEncoder::MessageEncoder()
{
    currentAlgorithm = nullptr;
    ROT3* rot3 = new ROT3();
    allAlgorithms.insert(std::make_pair(rot3->getName(), rot3));
    Mirror* mirror = new Mirror();
    allAlgorithms.insert(std::make_pair(mirror->getName(), mirror));
    Multiply41* multiply41 = new Multiply41();
    allAlgorithms.insert(std::make_pair(multiply41->getName(), multiply41));
}

MessageEncoder::~MessageEncoder()
{
    for (std::pair<std::string, BaseEncoderExecutor*> pair : allAlgorithms)
        delete pair.second;
}

bool MessageEncoder::addAlgorithm(BaseEncoderExecutor *algorithm)
{
    if (algorithm == nullptr)
        return false;
    allAlgorithms.insert(std::make_pair(algorithm->getName(), algorithm));
    return true;
}

bool MessageEncoder::chooseAlgorithm(std::string algorithm)
{
    if (allAlgorithms.find(algorithm) != allAlgorithms.end())
    {
        currentAlgorithm = allAlgorithms[algorithm];
        return true;
    }
    return false;
}

std::string MessageEncoder::decode(const std::string &message)
{
    std::string decodeMessage = currentAlgorithm->decode(message);
    return decodeMessage;
}

std::string MessageEncoder::encode(const std::string &message)
{
    std::string encodeMessage = currentAlgorithm->encode(message);
    return encodeMessage;
}

std::vector<std::string> MessageEncoder::getAllAlgorithms() {
    std::vector<std::string> allAlgsName = {};
    for (std::pair<std::string, BaseEncoderExecutor*> alg : allAlgorithms)
    {
        allAlgsName.push_back(alg.first);
    }
    return allAlgsName;
}
