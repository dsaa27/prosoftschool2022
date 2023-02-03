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
    using namespace Enumerations;
    testMeasureMessageSerialization(1, 5, "0 1 5");
    testMeasureMessageSerialization(2, 100, "0 2 100");
    testMeasureMessageSerialization(124124, 34, "0 124124 34");
    testMeasureMessageSerialization(35897320489273, 0, "0 35897320489273 0");
    testMeasureMessageSerialization(0, 0, "0 0 0");

    testCommandMessageSerialization(0.0, "1 0");
    testCommandMessageSerialization(0.01, "1 0.01");
    testCommandMessageSerialization(1.0 / 3, "1 0.333333");
    testCommandMessageSerialization(1.0 / 99, "1 0.010101");
    testCommandMessageSerialization(1.0 / 77, "1 0.012987");

    testErrorMessageSerialization(ErrorType::noSchedule, "2 0");
    testErrorMessageSerialization(ErrorType::noTimestamp, "2 1");
    testErrorMessageSerialization(ErrorType::obsolete, "2 2");

    testMeasureMessageDeserialization("0 1 5", 1, 5);
    testMeasureMessageDeserialization("0 2 100", 2, 100);
    testMeasureMessageDeserialization("0 124124 34", 124124, 34);
    testMeasureMessageDeserialization("0 35897320489273 0", 35897320489273, 0);
    testMeasureMessageDeserialization("0 0 0", 0, 0);

    testCommandMessageDeserialization("1 0", 0.0);
    testCommandMessageDeserialization("1 0.01", 0.01);
    testCommandMessageDeserialization("1 0.333333", 1.0 / 3);
    testCommandMessageDeserialization("1 0.010101", 1.0 / 99);
    testCommandMessageDeserialization("1 0.012987", 1.0 / 77);

    testErrorMessageDeserialization("2 0", ErrorType::noSchedule);
    testErrorMessageDeserialization("2 1", ErrorType::noTimestamp);
    testErrorMessageDeserialization("2 2", ErrorType::obsolete);
}
