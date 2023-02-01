#include "test_runner.h"
#include "tests.h"
#include <servermock/servertests.h>

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    RUN_TEST(tr, monitoringServerTest1);
    RUN_TEST(tr, monitoringServerTestErrorNoSchedule);
    RUN_TEST(tr, monitoringServerTestErrorNoTimestamp);
    RUN_TEST(tr, monitoringServerTestComplex);
    RUN_TEST(tr, monitoringServerTestNegativeValue);
    RUN_TEST(tr, monitoringServerTestStandardDeviation);
    RUN_TEST(tr, monitoringServerTestTwoDevices);
    return 0;
}


