#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include "baseencoderexecutor.h"
#include <unordered_map>

class MessageEncoder
{
public:
    MessageEncoder();
    ~MessageEncoder();

    std::string encode (const std::string &originMessage);

    std::string decode (const std::string &encodedMessage);

    void chooseCodingAlgorithm(const std::string& codeName);

    void registrateNewAlgorithm(BaseEncoderExecutor* newCoder);

private:
    std::unordered_map<std::string, BaseEncoderExecutor*> m_coderLibrary;
    BaseEncoderExecutor *m_chosenCodeAlgorithm;
};

#endif // MESSAGEENCODER_H
