#ifndef DEVICEMONITORINGSERVER_MESSAGEENCODER_H
#define DEVICEMONITORINGSERVER_MESSAGEENCODER_H


#include <string>
#include <map>
#include "BaseEncoderExecutor.h"

class MessageEncoder final
        {
public:
    MessageEncoder();
    ~MessageEncoder();
    std::string encode(std::string& message);
    std::string decode(std::string& message);
    bool chooseAlgorithm(std::string algorithm);
    bool addAlgorithm(BaseEncoderExecutor* algorithm);
private:
    BaseEncoderExecutor* currentAlgorithm;
    std::map<std::string, BaseEncoderExecutor*> allAlgorithms;
};


#endif //DEVICEMONITORINGSERVER_MESSAGEENCODER_H
