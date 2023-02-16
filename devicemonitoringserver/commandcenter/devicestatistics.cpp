#include "devicestatistics.h"

#include <cmath>

DeviceStatistics::DeviceStatistics(uint64_t deviceId) :
    m_deviceId(deviceId)
{}

double DeviceStatistics::getMeanSquaredError()
{
    int64_t sum = 0;
    for(int8_t value : m_values)
    {
        sum += value;
    }
    int m_valuesSize = m_values.size();
    double average = static_cast<double>(sum) / m_valuesSize;
    double mse = 0.0;
    for(int8_t value : m_values)
    {
        mse += pow(value - average, 2);
    }
    mse /= m_valuesSize;
    return sqrt(mse);
}

bool DeviceStatistics::addValue(uint64_t timeStamp, int8_t value)
{
    if (m_statistics.size() == 0)
    {
        m_values.push_back(value);
        m_statistics.emplace_back(PhaseStatistics{timeStamp, 0});
        return true;
    }
    PhaseStatistics lastElem = m_statistics.back();
    if(timeStamp < lastElem.timeStamp)
    {
        return false;
    }
    if(timeStamp > lastElem.timeStamp)
    {
        m_values.clear();
        m_values.push_back(value);
        m_statistics.emplace_back(PhaseStatistics{timeStamp, 0});
    }
    else if(timeStamp == lastElem.timeStamp)
    {
        m_values.push_back(value);
        m_statistics.back().meanSquaredError = getMeanSquaredError();
    }
    return true;
}

std::vector<PhaseStatistics> DeviceStatistics::getStatistics() const
{
    return std::vector<PhaseStatistics>(m_statistics);
}

uint64_t DeviceStatistics::getDeviceId() const
{
    return m_deviceId;
}
