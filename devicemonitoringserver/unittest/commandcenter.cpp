#include "unittest.h"
#include "../clientservercomponents/commandcenter.h"
#include "../test_runner.h"
#include "../randomgenerate.h"

#include <cmath>

void unitTest::commandCenterTask::setUnsetDeviceWorkSchedule()
{
    CommandCenter commandCenter;

    DeviceWorkSchedule *randomDeviceWorkSchedule1 = randomGenerate::createRandomDeviceWorkSchedule();
    uint64_t randomDeviceWorkSchedule1Id = randomDeviceWorkSchedule1->deviceId;

    DeviceWorkSchedule *randomDeviceWorkSchedule2 = randomGenerate::createRandomDeviceWorkSchedule();
    uint64_t randomDeviceWorkSchedule2Id = randomDeviceWorkSchedule2->deviceId;

    commandCenter.setDeviceWorkSchedule(randomDeviceWorkSchedule1);
    ASSERT_EQUAL(randomDeviceWorkSchedule1, commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule1Id));
    commandCenter.unsetDeviceWorkSchedule(randomDeviceWorkSchedule1Id);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule1Id), nullptr);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id), nullptr);
    commandCenter.unsetDeviceWorkSchedule(randomDeviceWorkSchedule2Id);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id), nullptr);
    commandCenter.setDeviceWorkSchedule(randomDeviceWorkSchedule2);
    ASSERT_EQUAL(randomDeviceWorkSchedule2, commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id));
    commandCenter.unsetDeviceWorkSchedule(randomDeviceWorkSchedule2Id);
    ASSERT_EQUAL(commandCenter.getDeviceWorkSchedule(randomDeviceWorkSchedule2Id), nullptr);

    delete randomDeviceWorkSchedule1;
    delete randomDeviceWorkSchedule2;
}

double unitTest::commandCenterTask::calculateStandardDeviation(double inaccuracy)
{
    static std::vector<double> allInaccuracies;

    allInaccuracies.push_back(inaccuracy);


    double average = 0;
    for (auto now : allInaccuracies) {
        average += now;
    }
    average /= allInaccuracies.size();

    double sumOfDeviationSquares= 0;

    for (auto now : allInaccuracies) {
        sumOfDeviationSquares += ((average - now) * (average - now));
    }

    return sqrt(sumOfDeviationSquares/allInaccuracies.size());
}

//void unitTest::commandCenterTask::standardDeviationCalculation()
//{
//    CommandCenter commandCenter;

//     uint64_t deviceId = 10213;
//     std::vector<Phase> correctScheduleVector = {{0, 14}, {10, 23}, {20, 5}, {30, 3}, {40, 99}, {55, 38}, {61, 34}};
//     DeviceWorkSchedule *correctDeviceWorkSchedule = new DeviceWorkSchedule(correctScheduleVector, deviceId);

//     commandCenter.setDeviceWorkSchedule(correctDeviceWorkSchedule);

//     const double epsilon = 1e-4;

//     sendOneCommandMessage(commandCenter, deviceId, {0, 14}, {0, 1});
//     ASSERT((calculateStandardDeviation(1 - 14) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

//     sendOneCommandMessage(commandCenter, deviceId, {10, 23}, {10, 43});
//     ASSERT((calculateStandardDeviation(43 - 23) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

//     sendOneCommandMessage(commandCenter, deviceId, {20, 5}, {20, 55});
//     ASSERT((calculateStandardDeviation(55 - 5) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

//     sendOneCommandMessage(commandCenter, deviceId, {30, 3}, {30, 15});
//     ASSERT((calculateStandardDeviation(15 - 3) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

//     sendOneCommandMessage(commandCenter, deviceId, {40, 99}, {40, 10});
//     ASSERT((calculateStandardDeviation(10 - 99) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

//     sendOneCommandMessage(commandCenter, deviceId, {55, 38}, {55, 38});
//     ASSERT((calculateStandardDeviation(38 - 38) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

//     sendOneCommandMessage(commandCenter, deviceId, {61, 34}, {61, 10});
//     ASSERT((calculateStandardDeviation(10 - 34) - commandCenter.getCurrentStandardDeviation(deviceId)) < epsilon);

//     commandCenter.unsetDeviceWorkSchedule(deviceId);

//     delete correctDeviceWorkSchedule;
//}
