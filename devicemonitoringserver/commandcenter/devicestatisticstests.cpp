#include "devicestatisticstests.h"
#include "devicestatistics.h"
#include "test_runner.h"
#include <vector>
#include <cmath>

void assertEqualPhaseStat(const PhaseStatistics& fstPhase, const PhaseStatistics& sndPhase)
{
    ASSERT_EQUAL(fstPhase.timeStamp, sndPhase.timeStamp);
    ASSERT(std::abs(fstPhase.meanSquaredError - sndPhase.meanSquaredError) < 10e-7);
}

void assertEqualPhaseStatVectors(const std::vector<PhaseStatistics>& fstVector, const std::vector<PhaseStatistics>& sndVector)
{
    int fstVectorSize = fstVector.size();
    ASSERT_EQUAL(fstVectorSize, sndVector.size());
    for(int i = 0; i < fstVectorSize; ++i)
    {
        assertEqualPhaseStat(fstVector[i], sndVector[i]);
    }
}

void deviceStatisticsTest()
{
    uint64_t id = 111;
    DeviceStatistics stat = DeviceStatistics(111);
    ASSERT_EQUAL(stat.getDeviceId(), id);

    ASSERT(stat.addValue(3, 1));
    ASSERT(stat.addValue(3, 2));
    ASSERT(stat.addValue(3, 3));
    ASSERT(stat.addValue(3, 4));

    double mse = sqrt((pow(1 - 2.5, 2) + pow(2 - 2.5, 2) + pow(3 - 2.5, 2) + pow(4 - 2.5, 2)) / 4);
    std::vector<PhaseStatistics> expected {PhaseStatistics {3, mse}};
    assertEqualPhaseStatVectors(stat.getStatistics(), expected);

    ASSERT(!stat.addValue(1, 5));

    ASSERT(stat.addValue(5, 3));
    ASSERT(stat.addValue(5, 2));
    ASSERT(stat.addValue(5, 0));
    ASSERT(stat.addValue(5, 1));
    mse = sqrt((pow(3 - 1.5, 2) + pow(2 - 1.5, 2) + pow(0 - 1.5, 2) + pow(1 - 1.5, 2)) / 4);
    expected.emplace_back(PhaseStatistics {5, mse});
    assertEqualPhaseStatVectors(stat.getStatistics(), expected);
}
