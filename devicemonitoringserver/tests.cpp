#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>

#include "deviceworkschedule.h"


std::vector <double> generateExpectedHistory(std::vector<uint8_t> &meterage, std::vector<Phase> shedule)
{
    std::vector <double> expectedCommand;

    double Command;

    for (int i = 0; i < shedule.size(); i++)
    {
        Command = shedule[i].value - meterage[i];
        expectedCommand.push_back(Command);
    }

    return expectedCommand;
}

void monitoringServerTest1()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 1;
    const uint64_t serverId = 13;

    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));

    std::vector<uint8_t> meterages {32,5,150,10};
    std::vector<Phase> phases {{0,1},{1,5},{2,250},{3,200}};
    DeviceWorkSchedule schedule {deviceId,phases};

    server.setDeviceWorkSchedule(schedule);

    device.setMeterages(meterages);

    RO3 ro3;
    BaseEncoderExecutor* p_ro3 = reinterpret_cast <BaseEncoderExecutor*> (&ro3);

    device.setEncodingAlgoritm(p_ro3);
    server.setEncodingAlgoritm(p_ro3);

    while (taskQueue.processTask())
        ;

    device.startMeterageSending();

    for (int i = 0; i < meterages.size()*2 + 2; i++)
            taskQueue.processTask();

    std::vector <double> responce = device.responce();

    std::vector <double> expected = generateExpectedHistory(meterages, phases);

    uint64_t responceSize = responce.size();

    uint64_t expectedSize = expected.size();

    ASSERT_EQUAL(responceSize, expectedSize);
    ASSERT_EQUAL(responce, expected);
}

void serialiserTest()
{
        std::string Type1 = {"Meterage"};
        uint8_t Meterage1 = 82;
        uint64_t Time1 = 5;
        double Command = -31;
        std::string Type_error = {"NoTimestamp"};

        MessageSerialiser Message;

        std::string MessageTest1 = {"Meterage 82 5"};
        std::string MessageTest2 = {"Command -31"};
        std::string MessageTest3 = {"Error NoTimestamp"};

        std::string ExpectedString1 = Message.serialize_Message(Meterage1,Time1);
        std::string ExpectedString2 = Message.serialize_Message(Command);
        std::string ExpectedString3 = Message.serialize_Message(Type_error);

        ASSERT_EQUAL(ExpectedString1,MessageTest1);
        ASSERT_EQUAL(ExpectedString2,MessageTest2);
        ASSERT_EQUAL(ExpectedString3,MessageTest3);

        ASSERT_EQUAL(Message.GetTypeMessage(ExpectedString1),Type1);
        ASSERT_EQUAL(Message.GetMeterage(ExpectedString1),Meterage1);
        ASSERT_EQUAL(Message.GetTimeStamp(ExpectedString1),Time1);
        ASSERT_EQUAL(Message.GetTypeError(ExpectedString3),Type_error);
        ASSERT_EQUAL(Message.GetCommand(ExpectedString2),Command);
}

void encodeTestRO3()
{
    std::string Type1 = {"Meterage"};
    uint8_t Meterage1 = 82;
    uint64_t Time1 = 5;

    MessageSerialiser Message;

    std::string SerializeString1 = Message.serialize_Message(Meterage1,Time1);

    RO3 ro3;

    RO3 *p_ro3 = &ro3;

    BaseEncoderExecutor *p_U = reinterpret_cast <BaseEncoderExecutor*> (p_ro3);

    MessageEncoder Encode;

    Encode.registration_algorithm(p_U);

    std::string ExpectedString1 = Encode.encode(SerializeString1);

    std::string MessageTest1 = {"Phwhudjh#;5#8"};

    std::string ExpectedString2 = Encode.decode(ExpectedString1);

    ASSERT_EQUAL(ExpectedString1,MessageTest1);
    ASSERT_EQUAL(ExpectedString2,SerializeString1);
}

void encodeTestMultiply()
{
    std::string Type1 = {"Meterage"};
    uint8_t Meterage1 = 82;
    uint64_t Time1 = 5;

    MessageSerialiser Message;

    std::string SerializeString1 = Message.serialize_Message(Meterage1,Time1);

    Multiply41 multiply;

    Multiply41 *p_multiply = &multiply;

    BaseEncoderExecutor *p_U = reinterpret_cast <BaseEncoderExecutor*> (p_multiply);

    MessageEncoder Encode;

    Encode.registration_algorithm(p_U);

    std::string ExpectedString1 = Encode.encode(SerializeString1);

    std::string MessageTest1 = {"3157 4141 4756 4141 4674 3977 4223 4141 1312 2296 2050 1312 2173 "};

    std::string ExpectedString2 = Encode.decode(ExpectedString1);

    ASSERT_EQUAL(ExpectedString1,MessageTest1);
    ASSERT_EQUAL(ExpectedString2,SerializeString1);
}

void encodeTestMirror()
{
    std::string Type1 = {"Meterage"};
    uint8_t Meterage1 = 82;
    uint64_t Time1 = 5;

    MessageSerialiser Message;

    std::string SerializeString1 = Message.serialize_Message(Meterage1,Time1);

    Mirror mirror;

    Mirror *p_mirror = &mirror;

    BaseEncoderExecutor *p_U = reinterpret_cast <BaseEncoderExecutor*> (p_mirror);

    MessageEncoder Encode;

    Encode.registration_algorithm(p_U);

    std::string ExpectedString1 = Encode.encode(SerializeString1);

    std::string MessageTest1 = {"5 28 egareteM"};

    std::string ExpectedString2 = Encode.decode(ExpectedString1);

    ASSERT_EQUAL(ExpectedString1,MessageTest1);
    ASSERT_EQUAL(ExpectedString2,SerializeString1);
}


