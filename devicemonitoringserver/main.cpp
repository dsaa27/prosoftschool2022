#include "test_runner.h"
#include "tests.h"
#include "servermock/servertests.h"
#include "unittest/unittest.h"

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

     //TODO: собственные тесты
    RUN_TEST(tr, monitoringServerTest1);
    RUN_TEST(tr, unitTest::messageSerializer);
    RUN_TEST(tr, unitTest::messageEncoder);
    RUN_TEST(tr, unitTest::commandCenter);
    return 0;
}
