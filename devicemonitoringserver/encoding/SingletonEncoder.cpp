#include "SingletonEncoder.h"

SingletonEncoder* SingletonEncoder::p_instance = nullptr;

MessageEncoder* SingletonEncoder::getDeviceEncoder(uint64_t deviceId) {
    addDeviceEncoder(deviceId);
    return m_devicesEncoder[deviceId];
}

void SingletonEncoder::addDeviceEncoder(uint64_t deviceId) {
    if (m_devicesEncoder.find(deviceId) != m_devicesEncoder.end() && m_devicesEncoder.find(deviceId)->second != nullptr)
        return;
    auto* messageEncoder = new MessageEncoder();
    m_devicesEncoder.insert(std::make_pair(deviceId, messageEncoder));
}

void SingletonEncoder::deleteDevice(uint64_t deviceId) {
    if (m_devicesEncoder.find(deviceId) != m_devicesEncoder.end())
        m_devicesEncoder.erase(deviceId);
    if (m_devicesEncoder.empty())
        delete p_instance;
}

SingletonEncoder::~SingletonEncoder() {
    for (std::pair<uint64_t, MessageEncoder*> pair : m_devicesEncoder)
        delete pair.second;
}

