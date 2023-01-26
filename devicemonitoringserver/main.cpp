#include "test_runner.h"
#include "tests.h"
#include "devicemock.h"
#include "abstractconnectionserver.h"
#include "connectionservermock.h"
#include "devicemonitoringserver.h"
#include <servermock/servertests.h>
#include <servermock/clientconnectionmock.h>
#include <vector>

int main()
{
    TaskQueue taskQueue;
    AbstractClientConnection* client = new ClientConnectionMock(taskQueue);
    AbstractConnectionServer* server = new ConnectionServerMock(taskQueue);
    DeviceMonitoringServer *monitoringServer = new DeviceMonitoringServer(server);
    DeviceMock *deviceMock = new DeviceMock(client);
    deviceMock->bind(13);
    monitoringServer->listen(13);

    if(deviceMock->connectToServer(server->listenedId()))
    {
        std::vector<uint8_t> mets = {32,1,1,1,1,2,3,33,4};
        std::vector<Phase> phases;
        while (taskQueue.processTask())
            ;
        for (uint64_t i = 1; i < mets.size() + 1; i++)
        {
            phases.push_back({i, mets[i - 1]});
        }
        DeviceWorkSchedule const deviceWorkSchedule = {13, phases};
        monitoringServer->setDeviceWorkSchedule(deviceWorkSchedule);
        deviceMock->setMeterages({32,1,1,1,1,2,3,33,4});
        deviceMock->startMeterageSending();
        for (uint64_t i = 0; i < mets.size()*2; i++)
            taskQueue.processTask();
    }


    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    // TODO: собственные тесты
   // RUN_TEST(tr, monitoringServerTest1);
    return 0;
}


