#ifndef DEVICEMONITORINGSERVER_SINGLETONENCODER_H
#define DEVICEMONITORINGSERVER_SINGLETONENCODER_H

#include <map>
#include <cstdint>
#include "MessageEncoder.h"

class SingletonEncoder {
    private:
        std::map<uint64_t, MessageEncoder*> devicesEncoder;
        static SingletonEncoder * p_instance;
        SingletonEncoder()=default;
    public:
        MessageEncoder* getDeviceEncoder(uint64_t deviceId);
        void addDeviceEncoder(uint64_t deviceId);
        static SingletonEncoder* getInstance() {
            if(!p_instance)
                p_instance = new SingletonEncoder();
            return p_instance;
        }
    };

#endif //DEVICEMONITORINGSERVER_SINGLETONENCODER_H
