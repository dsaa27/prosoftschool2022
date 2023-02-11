#ifndef RANDOMGENERATE_H
#define RANDOMGENERATE_H

#include "deviceworkschedule.h"

#include <cstddef>

namespace randomGenerate
{
    DeviceWorkSchedule* createRandomDeviceWorkSchedule();

    std::vector<uint8_t> createRandomMeterageVector(size_t vectorSize);
}

#endif // RANDOMGENERATE_H
