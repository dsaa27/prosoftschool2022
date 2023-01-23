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
        std::vector<uint64_t> mets = {2,1,1,1,1,2,3,33,4};
        while (taskQueue.processTask())
            ;
        //monitoringServer->setDeviceWorkSchedule(); //сделать
        deviceMock->setMeterages({2,1,1,1,1,2,3,33,4});
        deviceMock->startMeterageSending();
        for (uint64_t i = 0; i < mets.size()*2; i++)
            taskQueue.processTask();
    }


    TestRunner tr;
   /* RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);
*/
    // TODO: собственные тесты
   // RUN_TEST(tr, monitoringServerTest1);
    return 0;
}


