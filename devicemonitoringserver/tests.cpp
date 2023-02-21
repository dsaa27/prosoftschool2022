#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "servermock/clientconnectionmock.h"
#include "servermock/connectionservermock.h"
#include "servermock/taskqueue.h"
#include "test_runner.h"

#include <iostream>
using namespace std;

void
monitoringServerTest() {
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const std::uint64_t deviceId{1000u};
    const std::uint64_t serverId{1u};

    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));

    server.setDeviceWorkSchedule(
        {deviceId,
         {{0u, 92u}, {1u, 50u}, {2u, 19u}, {3u, 94u}, {4u, 90u}, {5u, 53u}}});

    device.setMeterages({89u, 50u, 3u, 8u, 38u, 78u});

    taskQueue.processTask();
    device.startMeterageSending();

    while (taskQueue.processTask())
        ;

    const std::vector<std::int8_t> responces{device.responces()};
    ASSERT_EQUAL(responces.size(), 6u);

    const std::vector<std::int8_t> expected{
        92 - 89 /* 2 */, 50 - 50 /* 0 */,  19 - 3 /* 16 */,
        94 - 8 /* 86 */, 90 - 38 /* 52 */, 53 - 78 /* -25 */
    };

    ASSERT_EQUAL(responces, expected);
}
