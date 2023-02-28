#include "test_runner.h"
#include "tests.h"
#include <servermock/servertests.h>
#include <iostream>

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    // TODO: собственные тесты
    RUN_TEST(tr, serializatorTest);
    RUN_TEST(tr, encoderTest);
    RUN_TEST(tr, comandCenterTest);
    RUN_TEST(tr, monitoringServerTest);

    return 0;
}
