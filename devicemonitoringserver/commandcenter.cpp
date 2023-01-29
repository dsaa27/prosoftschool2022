#include "commandcenter.h"
#include "deviceworkschedule.h"
#include <numeric>
#include <cmath>
#include <iostream>

Device::Device() {
    m_errors = new MyBuffer();
}

Device::~Device() {
    delete m_errors;
}

void Device::MyBuffer::push(const int& value) {
    if (tail<maxSize) {
        *(head++) = value;
        ++tail;
    } else {
        if (head != &buffer[maxSize]) {
            *(head++) = value;
        } else {
            head = &buffer[0];
            *(head++) = value;
        }
    }
}


CommandCenter::~CommandCenter() {
    if (!m_devices.empty()) {
        for (auto& it : m_devices) {
            delete it.second;
        }
    }
}

void CommandCenter::setSchedule(const DeviceWorkSchedule& workSchedule) {
    if (!workSchedule.deviceId) return;
    const auto& it = m_devices.find(workSchedule.deviceId);
    if (it == m_devices.end()) {
        auto *m_device = new Device;
        m_devices.insert({workSchedule.deviceId, m_device});
        m_device->m_deviceWorkSchedule = &workSchedule;
    }
    else {
        it->second->m_deviceWorkSchedule = &workSchedule;
    }
}

void CommandCenter::calculateMSE(uint64_t deviceId) const {
    const auto& it = m_devices.find(deviceId);
    auto errors = it->second->m_errors;
    double average = std::accumulate(errors->buffer, errors->buffer+errors->tail, 0)/errors->tail;
    std::vector<double> deviations;
    for (uint8_t i = 0; i < errors->tail; ++i)
        deviations.push_back(pow(std::abs(errors->buffer[i]-average), 2));
    it->second->m_MSE = std::ceil(sqrt(std::accumulate(deviations.begin(), deviations.end(), 0.0)/deviations.size())*multyplier)/multyplier;
};

double CommandCenter::getMSE(uint64_t deviceId) const {
    if (!deviceId) return 0.0;
    const auto& it = m_devices.find(deviceId);
    if (it == m_devices.end())
        return 0.0;
    else {
        return it->second->m_MSE;
    }
}

Message* CommandCenter::makeDecision(uint64_t deviceId, const Message* clientMeterage) {
    if (m_devices.count(deviceId) == 0) {
        return new Error(Error::Type::NoSchedule);
    }

    const auto& device = m_devices.find(deviceId);
    uint64_t& deviceExpTmstmp = device->second->m_expectedTimestamp;
    auto* currentMeterage =static_cast<const Meterage*>(clientMeterage);
    const uint64_t& clientCurrentTmstmp = currentMeterage->m_timestamp;

    if (deviceExpTmstmp > clientCurrentTmstmp) {
        ++deviceExpTmstmp;
        return new Error(Error::Type::Obsolete);
    } else {
        const auto& phase = device->second->m_deviceWorkSchedule->schedule;
        uint64_t left = 0;
        uint64_t right = phase.size()-1;
        uint64_t mid = (left+right)/2;

        while ((phase[mid].timeStamp != clientCurrentTmstmp) && left<right) {
            if (phase[mid].timeStamp < clientCurrentTmstmp)
                left = mid + 1;
            else right = mid - 1;
            mid = (left+right)/2;
        }
        if (phase[mid].timeStamp != clientCurrentTmstmp) {
            ++deviceExpTmstmp;
            return new Error(Error::Type::NoTimestamp);
        } else {
            auto* newCommand = new Command();
            int deviation = phase[mid].value-currentMeterage->m_value;
            newCommand->m_value = abs(deviation);
            newCommand->m_up = deviation >= 0 ? true : false;

            deviceExpTmstmp = clientCurrentTmstmp;
            ++deviceExpTmstmp;
            device->second->m_errors->push(deviation);
            calculateMSE(deviceId);
            return newCommand;
        }
    }
}
