#include "test_runner.h"
#include "tests.h"
#include <servertests.h>

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    RUN_TEST(tr, monitoringServerTest1);
    RUN_TEST(tr, monitoringServerTestErrorNoShedule);
    RUN_TEST(tr, monitoringServerTestErrorNoTimestamp);
    RUN_TEST(tr, monitoringServerTestErrorObsole);
    return 0;
}
