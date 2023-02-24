#include "test_runner.h"
#include "tests.h"
#include "servermock/servertests.h"

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    RUN_TEST(tr, encodingTest);
    RUN_TEST(tr, serializationTest);
    RUN_TEST(tr, monitoringServerTest1);
    RUN_TEST(tr, monitoringServerTest2);
    RUN_TEST(tr, monitoringServerTest3);
    RUN_TEST(tr, monitoringServerTest4);
    RUN_TEST(tr, monitoringServerTest5);
    //RUN_TEST(tr, BufferTest);
    return 0;
}
