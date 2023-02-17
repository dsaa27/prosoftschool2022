#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include "servermock/clientconnectionmock.h"
#include "servermock/connectionservermock.h"
#include "servermock/taskqueue.h"

#include <iostream>
using namespace std;

void monitoringServerTest1()
{
    // TODO: дописать тест
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const std::uint64_t deviceId{1000u};
    const std::uint64_t serverId{1u};

    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));

    server.setDeviceWorkSchedule({deviceId, {{0, 10}, {1, 20}, {2, 3}}});
    device.setMeterages({89, 2, 3});

    taskQueue.processTask();
    device.startMeterageSending();

    taskQueue.processTask();
    device.startMeterageSending();

    taskQueue.processTask();
    device.startMeterageSending();

    taskQueue.processTask();
    taskQueue.processTask();

    taskQueue.processTask();
    taskQueue.processTask();

    taskQueue.processTask();
    taskQueue.processTask();

    const std::vector<std::int8_t> responces{device.responces()};
    ASSERT_EQUAL(responces.size(), 3u);

    const std::vector<std::int8_t> expected{10 - 89, 20 - 2, 3 - 3};
    ASSERT_EQUAL(responces, expected);
}
