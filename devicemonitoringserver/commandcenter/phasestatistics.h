#ifndef PHASESTATISTICS_H
#define PHASESTATISTICS_H

#include <cstdint>

struct PhaseStatistics
{
    uint64_t timeStamp;
    double meanSquaredError;
};

#endif // PHASESTATISTICS_H
