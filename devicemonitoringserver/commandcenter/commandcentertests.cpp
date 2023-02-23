#include "commandcentertests.h"
#include "commandcenter.h"
#include "test_runner.h"
#include <vector>
#include <cmath>

void assertEqualPhaseStatVectors(const std::vector<PhaseStatistics>&, const std::vector<PhaseStatistics>&);

void assertEqualControl(const Control& fstCtrl, const Control& sndCtrl)
{
    ASSERT_EQUAL(fstCtrl.parameterTuning, sndCtrl.parameterTuning);
    ASSERT_EQUAL(fstCtrl.errorType, sndCtrl.errorType);
}

void commandCenterTest()
{
    CommandCenter center;

    /* DEVICE 111 */

    uint64_t id = 111;
    DeviceWorkSchedule* workSchedule = new DeviceWorkSchedule{id, std::vector<Phase>{{3, 5}, {5, 4}, {9, 4}}};

    assertEqualControl(center.checkDeviceWorkShedule(id, {3, 5}), Control{eNoSchedule});
    assertEqualPhaseStatVectors(center.getDeviceStatistics(id), std::vector<PhaseStatistics>());

    ASSERT(center.addDeviceWorkShedule(workSchedule));
    ASSERT(!center.addDeviceWorkShedule(workSchedule));

    assertEqualControl(center.checkDeviceWorkShedule(id, {2, 3}), Control{eNoTimestamp});

    assertEqualControl(center.checkDeviceWorkShedule(id, {4, 4}), Control{1});

    assertEqualControl(center.checkDeviceWorkShedule(id, {5, 1}), Control{3});
    assertEqualControl(center.checkDeviceWorkShedule(id, {6, 5}), Control{-1});
    assertEqualControl(center.checkDeviceWorkShedule(id, {6, 0}), Control{4});
    assertEqualControl(center.checkDeviceWorkShedule(id, {7, 4}), Control{0});
    assertEqualControl(center.checkDeviceWorkShedule(id, {8, 1}), Control{3});

    assertEqualControl(center.checkDeviceWorkShedule(id, {9, 6}), Control{-2});
    assertEqualControl(center.checkDeviceWorkShedule(id, {10, 3}), Control{1});

    assertEqualControl(center.checkDeviceWorkShedule(id, {9, 4}), Control{eObsolete});

    /* DEVICE 111 */


    /* DEVICE 222 */

    uint64_t id2 = 222;
    DeviceWorkSchedule* workSchedule2 = new DeviceWorkSchedule{id2, std::vector<Phase>{{4, 5}}};
    assertEqualControl(center.checkDeviceWorkShedule(id2, {4, 4}), Control{eNoSchedule});

    ASSERT(center.addDeviceWorkShedule(workSchedule2));
    ASSERT(!center.addDeviceWorkShedule(workSchedule2));

    assertEqualControl(center.checkDeviceWorkShedule(id2, {3, 3}), Control{eNoTimestamp});

    assertEqualControl(center.checkDeviceWorkShedule(id2, {4, 2}), Control{3});
    assertEqualControl(center.checkDeviceWorkShedule(id2, {4, 4}), Control{1});

    /* DEVICE 222 */


    /* DEVICE 111 */

    double mse2 = sqrt((pow(3 - 1.8, 2) + pow(-1 - 1.8, 2) + pow(4 - 1.8, 2) + pow(0 - 1.8, 2) + pow(3 - 1.8, 2)) / 5);
    double mse3 = sqrt((pow(-2 + 0.5, 2) + pow(1 + 0.5, 2)) / 2);
    assertEqualPhaseStatVectors(
                center.getDeviceStatistics(id),
                std::vector<PhaseStatistics>{PhaseStatistics{3, 0.0}, PhaseStatistics{5, mse2}, PhaseStatistics{9, mse3}});

    /* DEVICE 111 */


    /* DEVICE 222 */

    double mse_id2 = sqrt((pow(3 - 2, 2) + pow(1 - 2, 2)) / 2);
    assertEqualPhaseStatVectors(
                center.getDeviceStatistics(id2),
                std::vector<PhaseStatistics>{PhaseStatistics{4, mse_id2}});

    /* DEVICE 222 */
}
