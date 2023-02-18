#ifndef DEVICESTATISTICS_H
#define DEVICESTATISTICS_H

#include "phasestatistics.h"
#include <cstdint>
#include <vector>


class DeviceStatistics
{
public:
    DeviceStatistics(uint64_t deviceId);
    ~DeviceStatistics() = default;

    bool addValue(uint64_t timeStamp, int8_t value);
    std::vector<PhaseStatistics> getStatistics() const;
    uint64_t getDeviceId() const;

private:
    double getMeanSquaredError();

    const uint64_t m_deviceId;
    std::vector<PhaseStatistics> m_statistics;
    std::vector<int8_t> m_values;
};

#endif // DEVICESTATISTICS_H
