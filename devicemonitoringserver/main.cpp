#include "test_runner.h"
#include "tests.h"
#include <message/messageserializertests.h>
#include <messageencoder/encoderexecutorstests.h>
#include <servermock/servertests.h>

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    // TODO: собственные тесты
    RUN_TEST(tr, messageSerializerTest);

    RUN_TEST(tr, mirrorEncoderExecutorTest);
    RUN_TEST(tr, multiply41EncoderExecutorTest);
    RUN_TEST(tr, ROT3EncoderExecutorTest);


    RUN_TEST(tr, monitoringServerTest1);
    return 0;
}
