#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include "servermock/clientconnectionmock.h"
#include "servermock/connectionservermock.h"
#include "servermock/taskqueue.h"

//#include "clientservercomponents/messageserializer.h"
#include "unit_tests_functions/unittestfunctions.h"


void monitoringServerTest1()
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
    // device.setMeterages();
    // device.startMeterageSending();
    while (taskQueue.processTask())
        ;

    // ASSERT_EQUAL(device.responces(), expected);
}

void messageSerializerTest()
{
    using namespace unitTestFunctions;

    testMessageSerialization();
    testMessageDeserialization();
}

void commandCenterTest()
{
    using namespace unitTestFunctions;

    testCommandCenterSetUnsetDeviceWorkSchedule();
    testCommandCenterReceiveAndSendMessage();
    testStandardDeviationCalculation();
}
