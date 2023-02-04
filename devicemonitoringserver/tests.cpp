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
    testMeasureMessageSerialization(1, 5, "1 1 5");
    testMeasureMessageSerialization(2, 100, "1 2 100");
    testMeasureMessageSerialization(124124, 34, "1 124124 34");
    testMeasureMessageSerialization(35897320489273ULL, 0, "1 35897320489273 0");
    testMeasureMessageSerialization(0, 0, "1 0 0");

    testCommandMessageSerialization(0.0, "2 0");
    testCommandMessageSerialization(0.01, "2 0.01");
    testCommandMessageSerialization(1.0 / 3, "2 0.333333");
    testCommandMessageSerialization(1.0 / 99, "2 0.010101");
    testCommandMessageSerialization(1.0 / 77, "2 0.012987");

    testErrorMessageSerialization(ErrorType::noSchedule, "3 1");
    testErrorMessageSerialization(ErrorType::noTimestamp, "3 2");
    testErrorMessageSerialization(ErrorType::obsolete, "3 3");

    testMeasureMessageDeserialization("1 1 5", 1, 5);
    testMeasureMessageDeserialization("1 2 100", 2, 100);
    testMeasureMessageDeserialization("1 124124 34", 124124, 34);
    testMeasureMessageDeserialization("1 35897320489273 0", 35897320489273ULL, 0);
    testMeasureMessageDeserialization("1 0 0", 0, 0);

    testCommandMessageDeserialization("2 0", 0.0);
    testCommandMessageDeserialization("2 0.01", 0.01);
    testCommandMessageDeserialization("2 0.333333", 1.0 / 3);
    testCommandMessageDeserialization("2 0.010101", 1.0 / 99);
    testCommandMessageDeserialization("2 0.012987", 1.0 / 77);

    testErrorMessageDeserialization("3 1", ErrorType::noSchedule);
    testErrorMessageDeserialization("3 2", ErrorType::noTimestamp);
    testErrorMessageDeserialization("3 3", ErrorType::obsolete);

    testCheckInvalidDeserializeMessageArgument("-1 2 3", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1241 2 3", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1241 2 3", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1  5  8", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("0 92 034 35", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1 92 34 35", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1 -1", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("1 -1 4", "");
    testCheckInvalidDeserializeMessageArgument("1 24321", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("2 0.12411", "");
    testCheckInvalidDeserializeMessageArgument("2 342", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("2 -124", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("3 1", "");
    testCheckInvalidDeserializeMessageArgument("3 2", "");
    testCheckInvalidDeserializeMessageArgument("3 24321", "Deserializer has invalid argument");
    testCheckInvalidDeserializeMessageArgument("3 -1", "Deserializer has invalid argument");
}
