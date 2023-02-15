#include "test_runner.h"
#include "tests.h"
#include <servermock/servertests.h>


using namespace std;
int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);
    RUN_TEST(tr, monitoringServerTest1);

    RUN_TEST(tr,serialiserTest);
    RUN_TEST(tr,encodeTestRO3);
    RUN_TEST(tr,encodeTestMultiply);
    RUN_TEST(tr,encodeTestMirror);

    return 0;
}
