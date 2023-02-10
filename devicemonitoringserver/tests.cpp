#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include <encoding/Xor.h>

void monitoringServerStandardTest()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 1;
    const uint64_t serverId = 13;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector<uint8_t> mets = {32, 2};
    std::vector<Phase> phases;
    for (uint64_t i = 1; i < mets.size() + 1; i++)
        phases.emplace_back(Phase{i, mets[i - 1]});
    DeviceWorkSchedule const deviceWorkSchedule = {deviceId, phases};
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device.setMeterages({31, 2});
    std::vector<std::string> expected = {"1 1", "1 0"};
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (int i = 0; i < mets.size()*2 + 2; i++)
        taskQueue.processTask();

    std::vector<std::string> responses = device.getResponses();
    if (responses.size() != expected.size())
        ASSERT(false);
    for (int i = 0; i < responses.size(); i++)
        ASSERT_EQUAL(responses[i], expected[i]);
}

void monitoringServerTestErrorNoSchedule()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    device.setMeterages({31});
    std::vector<std::string> expected = {"2 101"};
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (int i = 0; i < 2; i++)
        taskQueue.processTask();
    std::vector<std::string> responses = device.getResponses();
    if (responses.size() != expected.size())
    ASSERT(false);
    for (int i = 0; i < responses.size(); i++)
        ASSERT_EQUAL(responses[i], expected[i]);
}

void monitoringServerTestErrorNoTimestamp()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 5;
    const uint64_t serverId = 4;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector<uint8_t> mets = {12};
    std::vector<Phase> phases;
    for (uint64_t i = 1; i < mets.size() + 1; i++)
        phases.emplace_back(Phase {i, mets[i - 1]});

    DeviceWorkSchedule const deviceWorkSchedule = {deviceId, phases};
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device.setMeterages({13, 1});
    std::vector<std::string> expected = {"1 -1", "2 102"};
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (int i = 0; i < mets.size()*2 + 2; i++)
        taskQueue.processTask();

    std::vector<std::string> responses = device.getResponses();
    if (responses.size() != expected.size())
    ASSERT(false);
    for (int i = 0; i < responses.size(); i++)
        ASSERT_EQUAL(responses[i], expected[i]);
}

void monitoringServerTestNegativeValue()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 6;
    const uint64_t serverId = 28;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector<uint8_t> mets = {3};
    std::vector<Phase> phases;
    for (uint64_t i = 1; i < mets.size() + 1; i++)
        phases.emplace_back(Phase {i, mets[i - 1]});

    DeviceWorkSchedule const deviceWorkSchedule = {deviceId, phases};
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device.setMeterages({5});
    std::vector<std::string> expected = {"1 -2"};
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (int i = 0; i < mets.size()*2 + 2; i++)
        taskQueue.processTask();

    std::vector<std::string> responses = device.getResponses();
    if (responses.size() != expected.size())
    ASSERT(false);
    for (int i = 0; i < responses.size(); i++)
        ASSERT_EQUAL(responses[i], expected[i]);
}

void monitoringServerTestComplex()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 12;
    const uint64_t serverId = 9;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector<uint8_t> mets = {31, 2, 4, 5, 6};
    std::vector<Phase> phases;
    for (uint64_t i = 1; i < mets.size() + 1; i++)
        phases.emplace_back(Phase {i, mets[i - 1]});

    DeviceWorkSchedule const deviceWorkSchedule = {deviceId, phases};
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device.setMeterages({31, 2, 8, 3, 7, 7});
    std::vector<std::string> expected = {"1 0", "1 0", "1 -4", "1 2", "1 -1", "2 102"};
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (int i = 0; i < mets.size()*2 + 2; i++)
        taskQueue.processTask();
    std::vector<std::string> responses = device.getResponses();
    if (responses.size() != expected.size())
        ASSERT(false);
    for (int i = 0; i < responses.size(); i++)
        ASSERT_EQUAL(responses[i], expected[i]);
}

void monitoringServerTestStandardDeviation()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector<uint8_t> mets = {31, 2, 4, 5, 6};
    std::vector<Phase> phases;
    for (uint64_t i = 1; i < mets.size() + 1; i++)
        phases.emplace_back(Phase{i, mets[i - 1]});
    DeviceWorkSchedule const deviceWorkSchedule = {deviceId, phases};
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device.setMeterages({31, 2, 8, 3, 7});
    std::vector<std::string> expected = {"1 0", "1 0", "1 -4", "1 2", "1 -1"};
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (int i = 0; i < mets.size()*2 + 2; i++)
        taskQueue.processTask();
    std::vector<std::string> responses = device.getResponses();
    if (responses.size() != expected.size())
    ASSERT(false);
    for (int i = 0; i < responses.size(); i++)
    {
        ASSERT_EQUAL(responses[i], expected[i]);
    }
    double sd = server.getStandardDeviation(deviceId);
    ASSERT_EQUAL(sd, 1.96);
}

void monitoringServerTestTwoDevices()
{
    TaskQueue taskQueue;
    DeviceMock device1(new ClientConnectionMock(taskQueue));
    DeviceMock device2(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId1 = 111;
    const uint64_t deviceId2 = 112;
    const uint64_t serverId = 11;
    ASSERT(device1.bind(deviceId1));
    ASSERT(device2.bind(deviceId2));
    ASSERT(server.listen(serverId));
    ASSERT(device1.connectToServer(serverId));
    ASSERT(device2.connectToServer(serverId));

    std::vector<uint8_t> mets2 = {1, 2, 3};
    std::vector<uint8_t> mets1 = {31, 2, 4, 5, 6};
    std::vector<Phase> phases;
    std::vector<Phase> phases2;
    for (uint64_t i = 1; i < mets1.size() + 1; i++)
        phases.emplace_back(Phase {i, mets1[i - 1]});
    for (uint64_t i = 1; i < mets2.size() + 1; i++)
        phases2.emplace_back(Phase {i, mets2[i - 1]});
    DeviceWorkSchedule const deviceWorkSchedule = {deviceId1, phases};
    DeviceWorkSchedule const deviceWorkSchedule2 = {deviceId2, phases2};

    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device1.setMeterages({31, 2, 8, 3, 7});

    server.setDeviceWorkSchedule(deviceWorkSchedule2);
    device2.setMeterages({1, 3, 4});


    while (taskQueue.processTask())
        ;
    device2.startMeterageSending();
    device1.startMeterageSending();
    for (int i = 0; i < mets1.size() * 2 + mets2.size() * 2 + 2; i++)
        taskQueue.processTask();

    std::vector<std::string> responsesDev1 = device1.getResponses();
    std::vector<std::string> responsesDev2 = device2.getResponses();

    std::vector<std::string> expectedDev1 = {"1 0", "1 0", "1 -4", "1 2", "1 -1"};
    std::vector<std::string> expectedDev2 = {"1 0", "1 -1", "1 -1"};

    if (responsesDev1.size() != expectedDev1.size())
        ASSERT(false);
    if (responsesDev2.size() != expectedDev2.size())
        ASSERT(false);

    for (int i = 0; i < responsesDev1.size(); i++)
        ASSERT_EQUAL(responsesDev1[i], expectedDev1[i]);
    for (int i = 0; i < responsesDev2.size(); i++)
        ASSERT_EQUAL(responsesDev2[i], expectedDev2[i]);
    double sd = server.getStandardDeviation(deviceId1);
    ASSERT_EQUAL(sd, 1.96);
    sd = server.getStandardDeviation(deviceId2);
    ASSERT_EQUAL(sd, 0.47);
}

void encodingTest()
{
    MessageEncoder* encoder = new MessageEncoder();
    std::vector<std::string> actualAlgs = encoder->getAvailableAlgorithms();
    std::vector<std::string> expectedAlgs = {"Mirror", "Multiply41", "ROT3"};
    ASSERT_EQUAL(expectedAlgs, actualAlgs);
    ASSERT(!encoder->encode("1234"));
    ASSERT(!encoder->decode("1234"));
    encoder->chooseAlgorithm("ROT3");
    ASSERT_EQUAL(*encoder->encode("1234"), "1237");
    ASSERT_EQUAL(encoder->addAlgorithm(nullptr), false);
    delete encoder;
}

void encodingTestRot3()
{
    MessageEncoder* encoder = new MessageEncoder();
    encoder->chooseAlgorithm("ROT3");
    ASSERT_EQUAL(*encoder->encode("1234"), "1237");
    ASSERT_EQUAL(*encoder->decode("1237"), "1234");
    ASSERT_EQUAL(*encoder->encode("12 34 -2"), "15 37 1");
    ASSERT_EQUAL(*encoder->decode("15 37 1"), "12 34 -2");
    delete encoder;
}

void encodingTestMirror()
{
    MessageEncoder* encoder = new MessageEncoder();
    encoder->chooseAlgorithm("Mirror");
    ASSERT_EQUAL(*encoder->encode("41 23"), "14 32");
    ASSERT_EQUAL(*encoder->decode("14 32"), "41 23");
    delete encoder;
}

void encodingTestMultiply41()
{
    MessageEncoder* encoder = new MessageEncoder();
    encoder->chooseAlgorithm("Multiply41");
    ASSERT_EQUAL(*encoder->encode("1 -11"), "41 -451");
    ASSERT_EQUAL(*encoder->decode("41 -451"), "1 -11");
    delete encoder;
}

void encodingTestXor()
{
    MessageEncoder* encoder = new MessageEncoder();
    Xor* xorAlg = new Xor();
    encoder->addAlgorithm(xorAlg);
    std::vector<std::string> actualAlgs = encoder->getAvailableAlgorithms();
    std::vector<std::string> expectedAlgs = {"Mirror", "Multiply41", "ROT3", "Xor"};
    ASSERT_EQUAL(expectedAlgs, actualAlgs);
    encoder->chooseAlgorithm("Xor");
    ASSERT_EQUAL(*encoder->encode("12"), "pq");
    ASSERT_EQUAL(*encoder->decode("pq"), "12");
    ASSERT_EQUAL(*encoder->encode("1 -2"), "pcoe");
    ASSERT_EQUAL(*encoder->decode("pcoe"), "1 -2");
    delete encoder;
}


