#include "randomgenerate.h"

#include <random>

DeviceWorkSchedule* randomGenerate::createRandomDeviceWorkSchedule()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<uint64_t> uint64_t_distribution;
    std::uniform_int_distribution<uint8_t> uint8_t_distribution(0, 100);

    uint64_t deviceId = uint64_t_distribution(generator);
    size_t size_of_schedule = uint8_t_distribution(generator);

    std::vector<Phase> schedule(size_of_schedule);


    uint64_t currentTimeStamp;
    uint8_t currentValue;
    for (size_t i = 0; i < size_of_schedule; i++) {
        currentValue = uint8_t_distribution(generator);
        schedule[i] = {i, currentValue};
    }

    return new DeviceWorkSchedule(schedule, deviceId);
}

DeviceWorkSchedule* randomGenerate::createRandomDeviceWorkSchedule(
        size_t scheduleSize, uint64_t startTimeStamp)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<uint64_t> uint64_t_distribution;
    std::uniform_int_distribution<uint8_t> uint8_t_distribution(0, 100);

    uint64_t deviceId = uint64_t_distribution(generator);

    std::vector<Phase> schedule(scheduleSize);

    uint64_t currentTimeStamp;
    uint8_t currentValue;
    for (size_t i = 0; i < scheduleSize; i++) {
        currentValue = uint8_t_distribution(generator);
        schedule[i] = {i + startTimeStamp, currentValue};
    }

    return new DeviceWorkSchedule(schedule, deviceId);
}

std::vector<uint8_t> randomGenerate::createRandomMeterageVector(size_t vectorSize)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<uint8_t> uint8_t_distribution(0, 100);

    std::vector<uint8_t> meterageVector(vectorSize);

    for(int i = 0; i < vectorSize; i++)
        meterageVector[i] = uint8_t_distribution(generator);

    return meterageVector;
}
