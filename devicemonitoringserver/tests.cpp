#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>

#include <cmath>

void assertEqualPhaseStatVectors(const std::vector<PhaseStatistics>&, const std::vector<PhaseStatistics>&);

void monitoringServerTest()
{
    // TODO: дописать тест
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));

    taskQueue.processTask(); // connect

    server.setDeviceWorkSchedule(DeviceWorkSchedule{deviceId, std::vector<Phase>{{3, 5}, {5, 4}, {9, 4}}});
    device.setMeterages(std::vector<Meterage> { {2, 5}, {4, 4}, {5, 1}, {6, 5},  {6, 0}, {7, 4}, {8, 1}, {9, 6}, {8, 4}, {10, 3} });


    device.startMeterageSending();

    while (taskQueue.processTask())
        ;

    auto res = device.getReceivedValues();
    ASSERT_EQUAL(device.getReceivedValues(), std::vector<int64_t>({1, 3, -1, 4, 0, 3, -2, 1}));
    ASSERT_EQUAL(device.getReceivedMessageTypes(),
                 std::vector<MessageType>({eError, eCommand, eCommand, eCommand, eCommand, eCommand, eCommand, eCommand, eError, eCommand}));

    double mse2 = sqrt((pow(3 - 1.8, 2) + pow(-1 - 1.8, 2) + pow(4 - 1.8, 2) + pow(0 - 1.8, 2) + pow(3 - 1.8, 2)) / 5);
    double mse3 = sqrt((pow(-2 + 0.5, 2) + pow(1 + 0.5, 2)) / 2);

    std::vector<PhaseStatistics> expectedStat{{3, 0.0}, {5, mse2}, {9, mse3}};

    assertEqualPhaseStatVectors(server.getDeviceStatistics(deviceId), expectedStat);
}
