#include "test_runner.h"
#include "tests.h"
#include <message/messageserializertests.h>
#include <messageencoder/encoderexecutorstests.h>
#include <messageencoder/messageencodertests.h>
#include <commandcenter/devicestatisticstests.h>
#include <commandcenter/commandcentertests.h>
#include <servermock/servertests.h>

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);


    RUN_TEST(tr, messageSerializerTest);

    RUN_TEST(tr, mirrorEncoderExecutorTest);
    RUN_TEST(tr, multiply41EncoderExecutorTest);
    RUN_TEST(tr, ROT3EncoderExecutorTest);
    RUN_TEST(tr, messageEncoderTest);

    RUN_TEST(tr, deviceStatisticsTest);
    RUN_TEST(tr, commandCenterTest);

    RUN_TEST(tr, monitoringServerTest);
    return 0;
}
