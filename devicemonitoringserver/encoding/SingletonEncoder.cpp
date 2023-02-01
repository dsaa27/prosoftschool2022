#include "SingletonEncoder.h"

SingletonEncoder* SingletonEncoder::p_instance = nullptr;

MessageEncoder* SingletonEncoder::getDeviceEncoder(uint64_t deviceId) {
    addDeviceEncoder(deviceId);
    return devicesEncoder[deviceId];
}

void SingletonEncoder::addDeviceEncoder(uint64_t deviceId) {
    if (devicesEncoder.find(deviceId) != devicesEncoder.end() && devicesEncoder.find(deviceId)->second != nullptr)
        return;
    auto* messageEncoder = new MessageEncoder();
    devicesEncoder.insert(std::make_pair(deviceId, messageEncoder));
}

void SingletonEncoder::deleteDevice(uint64_t deviceId) {
    if (devicesEncoder.find(deviceId) != devicesEncoder.end())
        devicesEncoder.erase(deviceId);
    if (devicesEncoder.empty())
        delete p_instance;
}

SingletonEncoder::~SingletonEncoder() {
    for (std::pair<uint64_t, MessageEncoder*> pair : devicesEncoder)
        delete pair.second;
}

