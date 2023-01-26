#include "SingletonEncoder.h"

SingletonEncoder* SingletonEncoder::p_instance = nullptr;

MessageEncoder* SingletonEncoder::getDeviceEncoder(uint64_t deviceId) {
    return devicesEncoder[deviceId];
}

void SingletonEncoder::addDeviceEncoder(uint64_t deviceId) {
    if (devicesEncoder.find(deviceId) != devicesEncoder.end())
        return;
    auto* messageEncoder = new MessageEncoder();
    devicesEncoder.insert(std::make_pair(deviceId, messageEncoder));
}

