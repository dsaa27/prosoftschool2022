#include "test_runner.h"
#include <servermock/servertests.h>
#include <message.h>
#include <tests.h>
#include <messageserializator.h>
#include <encoder/messageencoder.h>

int main()
{

    TestRunner tr;

    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);
    RUN_TEST(tr, monitoringServerTest1);
    RUN_TEST(tr, serializatorTest);
    RUN_TEST(tr, encoderTest);
    return 0;
}
