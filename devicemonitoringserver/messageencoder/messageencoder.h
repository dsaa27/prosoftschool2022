#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include "baseencoderexecutor.h"
#include <map>
#include <vector>

class MessageEncoder
{
public:
    MessageEncoder();
    ~MessageEncoder();
    MessageEncoder(const MessageEncoder&) = delete;
    MessageEncoder(MessageEncoder&&) = delete;
    MessageEncoder& operator=(const MessageEncoder&) = delete;
    MessageEncoder& operator=(const MessageEncoder&&) = delete;

    bool encode(const std::string& originalMessage, std::string& encodedMessage) const;
    bool decode(const std::string& encodedMessage, std::string& decodedMessage) const;
    bool setAlgorithm(const std::string& nameAlg);
    bool addAlgorithm(BaseEncoderExecutor* encoderExecutor);
    std::string getAlgName() const;
    std::vector<std::string> getAllAlgNames() const;
private:
    BaseEncoderExecutor* m_currentExecutor;
    std::map<std::string, BaseEncoderExecutor*> m_executors;
};

#endif // MESSAGEENCODER_H
