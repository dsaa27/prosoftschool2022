#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include "deviceworkschedule.h"
#include "servermock/clientconnectionmock.h"
#include "servermock/connectionservermock.h"
#include "servermock/taskqueue.h"
#include <vector>
#include <iostream>

void monitoringServerTest1()
{
    TaskQueue taskQueue;
	std::vector<std::string> messagesFromServer;
    std::unordered_map<uint64_t, std::vector<std::string>&> messagesFromDevices;
    DeviceMock device(new ClientConnectionMock(taskQueue), messagesFromServer);
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue), messagesFromDevices);

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
	std::vector<uint8_t> meterages {1};
    std::vector<Phase> phases {{0,1}};
    DeviceWorkSchedule schedule {deviceId, phases};

    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    server.selectEncodingMethod(ROT3);
    device.selectEncodingMethod(ROT3);
    while (taskQueue.processTask())
        ;
	const auto& messagesFromDevice = messagesFromDevices.find(deviceId)->second;
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice[0], "Device ID 111 connected");
    ASSERT_EQUAL(messagesFromServer.size(), 0u);
    device.setMeterages(meterages);
    server.setDeviceWorkSchedule(schedule);
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice[0], "Device ID 111 connected");
    ASSERT_EQUAL(messagesFromServer.size(), 1u);
    ASSERT_EQUAL(messagesFromServer[0], "Increase by 0 points");

    device.disconnect();
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromServer.size(), 1u);
    while (taskQueue.processTask())
        ;
    ASSERT_EQUAL(messagesFromDevice.size(), 2u);
    ASSERT_EQUAL(messagesFromDevice[1], "Device ID 111 disconnected");
    ASSERT_EQUAL(messagesFromServer.size(), 1u);
}

void monitoringServerTest2()
{
    TaskQueue taskQueue;
    std::vector<std::string> messagesFromServer;
    std::unordered_map<uint64_t, std::vector<std::string>&> messagesFromDevices;
    DeviceMock device(new ClientConnectionMock(taskQueue), messagesFromServer);
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue), messagesFromDevices);

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    std::vector<uint8_t> meterages {1};
    std::vector<Phase> phases {{0,58}};
    DeviceWorkSchedule schedule {deviceId, phases};

    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    server.selectEncodingMethod(ROT3);
    device.selectEncodingMethod(Multiply41);
    while (taskQueue.processTask())
        ;
    const auto& messagesFromDevice = messagesFromDevices.find(deviceId)->second;
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromServer.size(), 0u);
    device.setMeterages(meterages);
    server.setDeviceWorkSchedule(schedule);
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;
    ASSERT_EQUAL(messagesFromDevice.size(), 2u);
    //std::cout<<messagesFromDevice[0]<<std::endl;  //<- забавные расшифровки
    //std::cout<<messagesFromDevice[1]<<std::endl;  //<- забавные расшифровки
    ASSERT_EQUAL(messagesFromServer.size(), 0u);
}

void monitoringServerTest3(){
    TaskQueue taskQueue;
    std::vector<std::string> messagesFromServer;
    std::unordered_map<uint64_t, std::vector<std::string>&> messagesFromDevices;
    DeviceMock device(new ClientConnectionMock(taskQueue), messagesFromServer);
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue), messagesFromDevices);

    const uint64_t deviceId = 100;
    const uint64_t serverId = 11;
    std::vector<uint8_t> meterages {1,2,3,4,5,6};
    std::vector<Phase> phases {{0,10},{1,10},{2,10},{3,3},{4,3},{5,3}};
    DeviceWorkSchedule schedule {deviceId, phases};

    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    server.selectEncodingMethod(Mirror);
    device.selectEncodingMethod(Mirror);
    while (taskQueue.processTask())
        ;
    const auto& messagesFromDevice = messagesFromDevices.find(deviceId)->second;
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice[0], "Device ID 100 connected");
    ASSERT_EQUAL(messagesFromServer.size(), 0u);
    device.setMeterages(meterages);
    server.setDeviceWorkSchedule(schedule);
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice[0], "Device ID 100 connected");
    ASSERT_EQUAL(messagesFromServer.size(), 6u);
    ASSERT_EQUAL(messagesFromServer[0], "Increase by 9 points");
    ASSERT_EQUAL(messagesFromServer[1], "Increase by 8 points");
    ASSERT_EQUAL(messagesFromServer[2], "Increase by 7 points");
    ASSERT_EQUAL(messagesFromServer[3], "Decrease by 1 points");
    ASSERT_EQUAL(messagesFromServer[4], "Decrease by 2 points");
    ASSERT_EQUAL(messagesFromServer[5], "Decrease by 3 points");
    double deviceMSE = server.getMSE(deviceId);
    ASSERT_EQUAL(deviceMSE, 5.07);

    server.disconnect();
    while (taskQueue.processTask())
        ;
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice[0], "Device ID 100 connected");
    ASSERT_EQUAL(messagesFromServer.size(), 7u);
    ASSERT_EQUAL(messagesFromServer[6], "Server ID 11 disconnected");
}

void monitoringServerTest4(){
    TaskQueue taskQueue;
    std::vector<std::string> messagesFromServer;
    std::unordered_map<uint64_t, std::vector<std::string>&> messagesFromDevices;
    DeviceMock device(new ClientConnectionMock(taskQueue), messagesFromServer);
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue), messagesFromDevices);

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    server.selectEncodingMethod(Multiply41);
    device.selectEncodingMethod(Multiply41);
    while (taskQueue.processTask())
        ;
    const auto& messagesFromDevice = messagesFromDevices.find(deviceId)->second;
    ASSERT_EQUAL(messagesFromDevice.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice[0], "Device ID 111 connected");
    ASSERT_EQUAL(messagesFromServer.size(), 0u);
    //no schedule
    {
        std::vector<uint8_t> meterages {1,2};
        device.setMeterages(meterages);
        device.startMeterageSending();
        while (taskQueue.processTask())
            ;
        ASSERT_EQUAL(messagesFromDevice.size(), 1u);
        ASSERT_EQUAL(messagesFromDevice[0], "Device ID 111 connected");
        ASSERT_EQUAL(messagesFromServer.size(), 2u);
        ASSERT_EQUAL(messagesFromServer[0], "Error at timestamp 0: no such schedule");
        ASSERT_EQUAL(messagesFromServer[1], "Error at timestamp 1: no such schedule");
    }
    //no timestamp
    {
        std::vector<uint8_t> meterages {1,2,1,2,3,4,5,6};
        std::vector<Phase> phases {{2,10},{3,10},{5,10},{6,10}};
        DeviceWorkSchedule schedule {deviceId, phases};
        server.setDeviceWorkSchedule(schedule);
        device.setMeterages(meterages);

        device.startMeterageSending();
        while (taskQueue.processTask())
            ;
        ASSERT_EQUAL(messagesFromDevice.size(), 1u);
        ASSERT_EQUAL(messagesFromDevice[0], "Device ID 111 connected");
        ASSERT_EQUAL(messagesFromServer.size(), 8u);
        ASSERT_EQUAL(messagesFromServer[0], "Error at timestamp 0: no such schedule");
        ASSERT_EQUAL(messagesFromServer[1], "Error at timestamp 1: no such schedule");
        ASSERT_EQUAL(messagesFromServer[2], "Increase by 9 points");
        ASSERT_EQUAL(messagesFromServer[3], "Increase by 8 points");
        ASSERT_EQUAL(messagesFromServer[4], "Error at timestamp 4: no timestamp");
        ASSERT_EQUAL(messagesFromServer[5], "Increase by 6 points");
        ASSERT_EQUAL(messagesFromServer[6], "Increase by 5 points");
        ASSERT_EQUAL(messagesFromServer[7], "Error at timestamp 7: no timestamp");
    }
    //obsolete
    //работает >только< при раскомментировании двух участков в devicemock.cpp/sendNextMeterage
    //и bool-поля obsoleteErrorFlag в devicemock.h
    //(нужны для того, чтобы уменьшить timestamp у device'а и не выйти в runtime error)
    /*{
        std::vector<uint8_t> meterages {1,2,1,2,3,4,5,6,7,8};
        std::vector<Phase> phases {{2,10},{3,10},{5,10},{6,10},{8,10},{9,10}};
        DeviceWorkSchedule schedule {deviceId, phases};
        server.setDeviceWorkSchedule(schedule);
        device.setMeterages(meterages);

        device.startMeterageSending();
        while (taskQueue.processTask())
            ;
        ASSERT_EQUAL(messagesFromDevice.size(), 1u);
        ASSERT_EQUAL(messagesFromDevice[0], "Device ID 111 connected");
        ASSERT_EQUAL(messagesFromServer.size(), 10u);
        ASSERT_EQUAL(messagesFromServer[0], "Error at timestamp 0: no such schedule");
        ASSERT_EQUAL(messagesFromServer[1], "Error at timestamp 1: no such schedule");
        ASSERT_EQUAL(messagesFromServer[2], "Increase by 9 points");
        ASSERT_EQUAL(messagesFromServer[3], "Increase by 8 points");
        ASSERT_EQUAL(messagesFromServer[4], "Error at timestamp 4: no timestamp");
        ASSERT_EQUAL(messagesFromServer[5], "Increase by 6 points");
        ASSERT_EQUAL(messagesFromServer[6], "Increase by 5 points");
        ASSERT_EQUAL(messagesFromServer[7], "Error at timestamp 7: no timestamp");
        ASSERT_EQUAL(messagesFromServer[8], "Increase by 3 points");
        ASSERT_EQUAL(messagesFromServer[9], "Error at timestamp 7: obsolete timestamp");
    }*/
}

void monitoringServerTest5(){
    TaskQueue taskQueue;

    const uint64_t deviceId1 = 100;
    std::vector<std::string> messagesFromServer1;
    DeviceMock device1(new ClientConnectionMock(taskQueue), messagesFromServer1);
    std::vector<uint8_t> meterages1 {1,2,3};
    std::vector<Phase> phases1 {{0,10},{1,10},{2,10}};
    DeviceWorkSchedule schedule1 {deviceId1, phases1};

    const uint64_t deviceId2 = 101;
    std::vector<std::string> messagesFromServer2;
    DeviceMock device2(new ClientConnectionMock(taskQueue), messagesFromServer2);
    std::vector<uint8_t> meterages2 {3,57,65};
    std::vector<Phase> phases2 {{0,55},{1,57},{2,59}};
    DeviceWorkSchedule schedule2 {deviceId2, phases2};

    const uint64_t serverId = 11;
    std::unordered_map<uint64_t, std::vector<std::string>&> messagesFromDevices;
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue), messagesFromDevices);

    ASSERT(device1.bind(deviceId1));
    ASSERT(device2.bind(deviceId2));
    ASSERT(server.listen(serverId));
    ASSERT(device1.connectToServer(serverId));
    ASSERT(device2.connectToServer(serverId));
    server.selectEncodingMethod(Custom);
    device1.selectEncodingMethod(Custom);
    device2.selectEncodingMethod(Custom);
    while (taskQueue.processTask())
        ;
    const auto& messagesFromDevice1 = messagesFromDevices.find(deviceId1)->second;
    const auto& messagesFromDevice2 = messagesFromDevices.find(deviceId2)->second;
    ASSERT_EQUAL(messagesFromDevice1.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice1[0], "Device ID 100 connected");
    device1.setMeterages(meterages1);
    server.setDeviceWorkSchedule(schedule1);
    ASSERT_EQUAL(messagesFromServer1.size(), 0u);

    ASSERT_EQUAL(messagesFromDevice2.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice2[0], "Device ID 101 connected");
    device2.setMeterages(meterages2);
    server.setDeviceWorkSchedule(schedule2);
    ASSERT_EQUAL(messagesFromServer2.size(), 0u);

    device1.startMeterageSending();
    device2.startMeterageSending();
    while (taskQueue.processTask())
        ;
    ASSERT_EQUAL(messagesFromDevice1.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice1[0], "Device ID 100 connected");
    ASSERT_EQUAL(messagesFromServer1.size(), 3u);
    ASSERT_EQUAL(messagesFromServer1[0], "Increase by 9 points");
    ASSERT_EQUAL(messagesFromServer1[1], "Increase by 8 points");
    ASSERT_EQUAL(messagesFromServer1[2], "Increase by 7 points");
    double deviceMSE1 = server.getMSE(deviceId1);
    ASSERT_EQUAL(deviceMSE1, 0.82);

    ASSERT_EQUAL(messagesFromDevice2.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice2[0], "Device ID 101 connected");
    ASSERT_EQUAL(messagesFromServer2.size(), 3u);
    ASSERT_EQUAL(messagesFromServer2[0], "Increase by 52 points");
    ASSERT_EQUAL(messagesFromServer2[1], "Increase by 0 points");
    ASSERT_EQUAL(messagesFromServer2[2], "Decrease by 6 points");
    double deviceMSE2 = server.getMSE(deviceId2);
    ASSERT_EQUAL(deviceMSE2, 26.05);

    server.disconnect();
    while (taskQueue.processTask())
        ;
    ASSERT_EQUAL(messagesFromDevice1.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice1[0], "Device ID 100 connected");
    ASSERT_EQUAL(messagesFromDevice2.size(), 1u);
    ASSERT_EQUAL(messagesFromDevice2[0], "Device ID 101 connected");
    ASSERT_EQUAL(messagesFromServer1.size(), 4u);
    ASSERT_EQUAL(messagesFromServer1[3], "Server ID 11 disconnected");
    ASSERT_EQUAL(messagesFromServer2.size(), 4u);
    ASSERT_EQUAL(messagesFromServer2[3], "Server ID 11 disconnected");
}

void encodingTest() {
    MessageEncoder testEncoder;
    //casual switching
    {
        ASSERT_EQUAL(testEncoder.getName(), "No name");
        testEncoder.selectMethod(ROT3);
        ASSERT_EQUAL(testEncoder.getName(), "ROT3");
        testEncoder.selectMethod(Mirror);
        ASSERT_EQUAL(testEncoder.getName(), "Mirror");
        testEncoder.selectMethod(Multiply41);
        ASSERT_EQUAL(testEncoder.getName(), "Multiply41");
        testEncoder.selectMethod(Custom);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.deselect();
        ASSERT_EQUAL(testEncoder.getName(), "No name");
    }
    //numbers
    {
        //ROT3
        std::string messageToEncode{"0123456789"};
        std::string messageEncoded{""};
        std::string messageDecoded{""};
        ASSERT_EQUAL(testEncoder.getName(), "No name");
        testEncoder.selectMethod(ROT3);
        ASSERT_EQUAL(testEncoder.getName(), "ROT3");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "ROT3");
        ASSERT_EQUAL(messageEncoded, "3456789012");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "ROT3");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //Mirror
        testEncoder.selectMethod(Mirror);
        ASSERT_EQUAL(testEncoder.getName(), "Mirror");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Mirror");
        ASSERT_EQUAL(messageEncoded, "9876543210");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Mirror");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //Multiply41
        testEncoder.selectMethod(Multiply41);
        ASSERT_EQUAL(testEncoder.getName(), "Multiply41");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Multiply41");
        ASSERT_EQUAL(messageEncoded, "04182123164205246287328369");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Multiply41");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //Custom
        //regular key
        testEncoder.selectMethod(Custom);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //custom key up to 10 symbols
        std::string key {"SomeKey"};
        testEncoder.registerСustom(key);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //custom key more than 10 symbols
        key = "SomeKeyMoreThan10Symbols";
        testEncoder.registerСustom(key);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        ASSERT_EQUAL(messageDecoded, messageToEncode);

        testEncoder.deselect();
        ASSERT_EQUAL(testEncoder.getName(), "No name");
    }
    //alphabet
    {
        //ROT3
        std::string messageToEncode{"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        std::string messageEncoded{""};
        std::string messageDecoded{""};
        ASSERT_EQUAL(testEncoder.getName(), "No name");
        testEncoder.selectMethod(ROT3);
        ASSERT_EQUAL(testEncoder.getName(), "ROT3");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "ROT3");
        ASSERT_EQUAL(messageEncoded, "defghijklmnopqrstuvwxyzabc DEFGHIJKLMNOPQRSTUVWXYZABC");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "ROT3");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //Mirror
        testEncoder.selectMethod(Mirror);
        ASSERT_EQUAL(testEncoder.getName(), "Mirror");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Mirror");
        ASSERT_EQUAL(messageEncoded, "zyxwvutsrqponmlkjihgfedcba ZYXWVUTSRQPONMLKJIHGFEDCBA");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Mirror");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //Multiply41
        testEncoder.selectMethod(Multiply41);
        ASSERT_EQUAL(testEncoder.getName(), "Multiply41");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Multiply41");
        ASSERT_EQUAL(messageEncoded, messageToEncode);
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Multiply41");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //Custom
        //regular key
        testEncoder.selectMethod(Custom);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //custom key up to 10 symbols
        std::string key {"SomeKey"};
        testEncoder.registerСustom(key);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        ASSERT_EQUAL(messageDecoded, messageToEncode);
        messageEncoded.clear();
        messageDecoded.clear();
        //custom key more than 10 symbols
        key = "SomeKeyMoreThan10Symbols";
        testEncoder.registerСustom(key);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedEncoding(messageEncoded, messageToEncode);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        testEncoder.proceedDecoding(messageDecoded, messageEncoded);
        ASSERT_EQUAL(testEncoder.getName(), "Custom");
        ASSERT_EQUAL(messageDecoded, messageToEncode);

        testEncoder.deselect();
        ASSERT_EQUAL(testEncoder.getName(), "No name");
    }
}

void serializationTest()
{
    MessageSerializator testSerializator;
    std::string serializedMessage{""};
    {
        auto* testMeterage = new Meterage{123, 20};
        serializedMessage = testSerializator.serialize(testMeterage);
        ASSERT_EQUAL(serializedMessage, "0 123 20");
        auto* deserializedMeterage = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testMeterage->m_type, deserializedMeterage->m_type);
        ASSERT_EQUAL(testMeterage->m_timestamp, static_cast<Meterage*>(deserializedMeterage)->m_timestamp);
        ASSERT_EQUAL(testMeterage->m_value, static_cast<Meterage*>(deserializedMeterage)->m_value);
        delete testMeterage;
        delete deserializedMeterage;
        serializedMessage.clear();
    }
    {
        auto* testCommand = new Command {12, true};
        serializedMessage = testSerializator.serialize(testCommand);
        ASSERT_EQUAL(serializedMessage, "1 12 1");
        auto* deserializedCommand = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testCommand->m_type, static_cast<Command*>(deserializedCommand)->m_type);
        ASSERT_EQUAL(testCommand->m_value, static_cast<Command*>(deserializedCommand)->m_value);
        ASSERT_EQUAL(testCommand->m_up, static_cast<Command*>(deserializedCommand)->m_up);
        delete testCommand;
        delete deserializedCommand;
        serializedMessage.clear();
    }
    {
        auto* testCommand = new Command {24, false};
        serializedMessage = testSerializator.serialize(testCommand);
        ASSERT_EQUAL(serializedMessage, "1 24 0");
        auto* deserializedCommand = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testCommand->m_type, static_cast<Command*>(deserializedCommand)->m_type);
        ASSERT_EQUAL(testCommand->m_value, static_cast<Command*>(deserializedCommand)->m_value);
        ASSERT_EQUAL(testCommand->m_up, static_cast<Command*>(deserializedCommand)->m_up);
        delete testCommand;
        delete deserializedCommand;
        serializedMessage.clear();
    }
    {
        auto* testErrNoSch = new Error{Error::Type::NoSchedule};
        serializedMessage = testSerializator.serialize(testErrNoSch);
        ASSERT_EQUAL(serializedMessage, "2 0");
        auto* deserializedError = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testErrNoSch->m_type, static_cast<Error*>(deserializedError)->m_type);
        ASSERT_EQUAL(testErrNoSch->m_errType, static_cast<Error*>(deserializedError)->m_errType);
        delete testErrNoSch;
        delete deserializedError;
        serializedMessage.clear();
    }
    {
        auto* testErrNoTmst = new Error{Error::Type::NoTimestamp};
        serializedMessage = testSerializator.serialize(testErrNoTmst);
        ASSERT_EQUAL(serializedMessage, "2 1");
        auto* deserializedError = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testErrNoTmst->m_type, static_cast<Error*>(deserializedError)->m_type);
        ASSERT_EQUAL(testErrNoTmst->m_errType, static_cast<Error*>(deserializedError)->m_errType);
        delete testErrNoTmst;
        delete deserializedError;
        serializedMessage.clear();
    }
    {
        auto* testObsolete = new Error{Error::Type::Obsolete};
        serializedMessage = testSerializator.serialize(testObsolete);
        ASSERT_EQUAL(serializedMessage, "2 2");
        auto* deserializedError = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testObsolete->m_type, static_cast<Error*>(deserializedError)->m_type);
        ASSERT_EQUAL(testObsolete->m_errType, static_cast<Error*>(deserializedError)->m_errType);
        delete testObsolete;
        delete deserializedError;
        serializedMessage.clear();
    }
    {
        auto* testObsolete = new Error{Error::Type::ErrorMessage};
        serializedMessage = testSerializator.serialize(testObsolete);
        ASSERT_EQUAL(serializedMessage, "2 100");
        auto* deserializedError = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testObsolete->m_type, static_cast<Error*>(deserializedError)->m_type);
        ASSERT_EQUAL(testObsolete->m_errType, static_cast<Error*>(deserializedError)->m_errType);
        delete testObsolete;
        delete deserializedError;
        serializedMessage.clear();
    }
    {
        auto* testInfo = new Info{"Test Info Message"};
        serializedMessage = testSerializator.serialize(testInfo);
        ASSERT_EQUAL(serializedMessage, "3 Test Info Message");
        auto* deserializedInfo = testSerializator.deserialize(serializedMessage);
        ASSERT_EQUAL(testInfo->m_type, static_cast<Info*>(deserializedInfo)->m_type);
        ASSERT_EQUAL(testInfo->m_message, static_cast<Info*>(deserializedInfo)->m_message);
        delete testInfo;
        delete deserializedInfo;
    }
}

/*
//поля класса MyBuffer (commandcenter.h/device) делал публичными, размер массива buffer - 4.
//Тест пройден успешно. В основной программе буфер хранит вплоть до 20 последних отклонений
void BufferTest() {
    Device device;
    device.m_errors->push(0);
    ASSERT_EQUAL(device.m_errors->buffer[0], 0);
    ASSERT_EQUAL(device.m_errors->tail, 1);
    ASSERT_EQUAL(device.m_errors->maxSize, 4);
    device.m_errors->push(1);
    ASSERT_EQUAL(device.m_errors->buffer[0], 0);
    ASSERT_EQUAL(device.m_errors->buffer[1], 1);
    ASSERT_EQUAL(device.m_errors->tail, 2);
    ASSERT_EQUAL(device.m_errors->maxSize, 4);
    device.m_errors->push(2);
    ASSERT_EQUAL(device.m_errors->buffer[0], 0);
    ASSERT_EQUAL(device.m_errors->buffer[1], 1);
    ASSERT_EQUAL(device.m_errors->buffer[2], 2);
    ASSERT_EQUAL(device.m_errors->tail, 3);
    ASSERT_EQUAL(device.m_errors->maxSize, 4);
    device.m_errors->push(3);
    ASSERT_EQUAL(device.m_errors->buffer[0], 0);
    ASSERT_EQUAL(device.m_errors->buffer[1], 1);
    ASSERT_EQUAL(device.m_errors->buffer[2], 2);
    ASSERT_EQUAL(device.m_errors->buffer[3], 3);
    ASSERT_EQUAL(device.m_errors->tail, 4);
    ASSERT_EQUAL(device.m_errors->maxSize, 4);
    device.m_errors->push(4);
    ASSERT_EQUAL(device.m_errors->buffer[0], 4);
    ASSERT_EQUAL(device.m_errors->buffer[1], 1);
    ASSERT_EQUAL(device.m_errors->buffer[2], 2);
    ASSERT_EQUAL(device.m_errors->buffer[3], 3);
    ASSERT_EQUAL(device.m_errors->tail, 4);
    ASSERT_EQUAL(device.m_errors->maxSize, 4);
}
*/
