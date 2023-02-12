#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include "servermock/clientconnectionmock.h"
#include "servermock/connectionservermock.h"
#include "servermock/taskqueue.h"
#include "randomgenerate.h"


namespace
{

std::vector<std::string> makeExpectedResponseStrings(
        CommandCenter &commandCenter, DeviceWorkSchedule deviceWorkSchedule,
        const std::vector<uint8_t> &meterages)
{
    commandCenter.setDeviceWorkSchedule(new DeviceWorkSchedule(deviceWorkSchedule));
    const uint64_t deviceId = deviceWorkSchedule.deviceId;

    std::vector<std::string> expectedResponseStrings(meterages.size());

    MeterageMessage *currentMeterageMessage;
    AbstractMessage *currentExpectedMessage;
    for (uint64_t timeStamp = 0; timeStamp < meterages.size(); timeStamp++) {
        currentMeterageMessage = new MeterageMessage(timeStamp, meterages[timeStamp]);
        currentExpectedMessage =
                commandCenter.receiveAndSendMessage(deviceId, currentMeterageMessage);
        expectedResponseStrings[timeStamp] = currentExpectedMessage->convert2string();
        delete currentExpectedMessage;
    }

    return expectedResponseStrings;
}

std::vector<std::string> makeResponseStrings
    (const std::vector<AbstractMessage*> responses)
{
    std::vector<std::string> responsesStrings(responses.size());
    for (int i = 0; i < responses.size(); i++)
        responsesStrings[i] = responses[i]->convert2string();

    return responsesStrings;
}

double makeExpectedStandardDeviation (CommandCenter &commandCenter, uint64_t deviceId)
{
    return commandCenter.getCurrentStandardDeviation(deviceId);
}

} //namespace

void monitoringServerTest1()
{
    const size_t meterageDataSize = 10;
    DeviceWorkSchedule *deviceWorkSchedule =
            randomGenerate::createRandomDeviceWorkSchedule(meterageDataSize);
    std::vector<uint8_t> meterages =
            randomGenerate::createRandomMeterageVector(meterageDataSize);

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


    CommandCenter testingCommandCenter;

    std::vector<std::string> reponseStrings =
            makeResponseStrings(device.response());
    std::vector<std::string> expectedResponsesStrings =
            makeExpectedResponseStrings(testingCommandCenter, *deviceWorkSchedule, meterages);

    ASSERT_EQUAL(reponseStrings, expectedResponsesStrings);

    double expectedStandardDeviation =
            makeExpectedStandardDeviation(testingCommandCenter, deviceId);
    double standardDeviation =
            server.getCurrentStandardDeviation(deviceId);
    const double epsilon = 1e-6;

    ASSERT(std::abs(standardDeviation - expectedStandardDeviation) < epsilon);
}
