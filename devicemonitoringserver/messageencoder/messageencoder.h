#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include "baseencoderexecutor.h"
#include "common.h"

#include <map>
#include <vector>

class MessageEncoder
{
    NON_COPYABLE(MessageEncoder);
public:
    MessageEncoder();
    ~MessageEncoder();

    bool encode(const std::string& originalMessage, std::string& encodedMessage) const;
    bool decode(const std::string& encodedMessage, std::string& decodedMessage) const;
    bool setAlgorithm(const std::string& algName);
    bool addAlgorithm(BaseEncoderExecutor* encoderExecutor);
    bool getAlgName(std::string& algName) const;
    std::vector<std::string> getAllAlgNames() const;
private:
    BaseEncoderExecutor* m_currentExecutor;
    std::map<std::string, BaseEncoderExecutor*> m_executors;
};

#endif // MESSAGEENCODER_H
