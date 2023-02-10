#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include "servermock/clientconnectionmock.h"
#include "servermock/connectionservermock.h"
#include "servermock/taskqueue.h"
#include "unit_tests_functions/unittestfunctions.h"
#include "unit_tests_functions/testmessageencoderfunctions.h"


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

void messageEncoderTest()
{
    using namespace testMessageEncoderFunctions;

    testROT3CodingAlgorithm();
    testMirrorCodingAlgorithm();
    testMultiply41CodingAlgorithm();
}

void monitoringServerTest1()
{
    using namespace Enumerations;
    // TODO: дописать тест
    CommandCenter testingCommandMessage;
    MessageSerializer testingMessageSerializer;
    DeviceWorkSchedule *deviceWorkSchedule = unitTestFunctions::createRandomDeviceWorkSchedule();
    testingCommandMessage.setDeviceWorkSchedule(new DeviceWorkSchedule(*deviceWorkSchedule));
    size_t meterageDataSize = deviceWorkSchedule->schedule.size();
    std::vector<uint8_t> meterages = unitTestFunctions::createRandomMeterageVector(meterageDataSize);

    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = deviceWorkSchedule->deviceId;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    while (taskQueue.processTask())
        ;
    device.setMeterages(meterages);
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;

    const std::vector<AbstractMessage*>& responseMessages = device.response();

    ASSERT_EQUAL(responseMessages.size(), meterageDataSize);

    const double epsilon = 1e-5;
    for (size_t timeStampMock = 0; timeStampMock < meterageDataSize; timeStampMock++)
    {
        AbstractMessage *responseAbstractMessage = responseMessages[timeStampMock];
        MeterageMessage *temporaryMeterageMessage = new MeterageMessage(timeStampMock, meterages[timeStampMock]);
        AbstractMessage *expectedAbstractMessage = testingCommandMessage.receiveAndSendMessage(deviceId, temporaryMeterageMessage);

        ASSERT_EQUAL(static_cast<int>(expectedAbstractMessage->getMessageType()),
                     static_cast<int>(responseAbstractMessage->getMessageType()));

        if (static_cast<int>(MessageType::command) == static_cast<int>(expectedAbstractMessage->getMessageType())) {
            CommandMessage *expectedCommandMessage = dynamic_cast<CommandMessage*>(expectedAbstractMessage);
            CommandMessage *responseCommandMessage = dynamic_cast<CommandMessage*>(responseAbstractMessage);
            ASSERT(std::abs(expectedCommandMessage->correction - responseCommandMessage->correction) < epsilon);

            delete expectedCommandMessage;
        } else {
            ErrorMessage *expectedErrorMessage = dynamic_cast<ErrorMessage*>(expectedAbstractMessage);
            ErrorMessage *responseErrorMessage = dynamic_cast<ErrorMessage*>(responseAbstractMessage);

            ASSERT(expectedErrorMessage->errorType == responseErrorMessage->errorType);

            delete expectedErrorMessage;
        }

        delete temporaryMeterageMessage;
    }

    ASSERT_EQUAL(testingCommandMessage.getCurrentStandardDeviation(deviceId), server.getCurrentStandardDeviation(deviceId));

    // ASSERT_EQUAL(device.responces(), expected);

}
