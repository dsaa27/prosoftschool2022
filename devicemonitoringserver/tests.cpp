#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include <message.h>

void monitoringServerTest1()
{
    // TODO: дописать тест
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector <uint8_t> meterages = {5, 6, 10, 20};
    device.setMeterages(meterages);
//    device.startMeterageSending();
//    while (taskQueue.processTask())
//        ;

    //ASSERT_EQUAL(device.responces(), expected);
}

void serializatorTest(){

    std::string SerializedString;
    Message * DeserializedString;
    MessageSerializator serializator;
    Meterages TestMeterages(255, 2);
    Message * message1 = &TestMeterages;

    SerializedString = serializator.Serialize(message1);
    DeserializedString = serializator.DeSerialize(SerializedString);
    Meterages * deserializedMeterage = dynamic_cast<Meterages*>(DeserializedString);

    ASSERT_EQUAL(TestMeterages.timeStamp, deserializedMeterage->timeStamp);

}

void encoderTest(){

    std::string TestString = "a bcdefghijklmnop1234567890!@#$%^&*()";
    MessageEncoder encoder;
    encoder.SetEncodeAlgorithm("Mirror");
    std::string ResultAfterMirror = encoder.encode(TestString);
    std::string ResultAfterDecoderMirror = encoder.decode(ResultAfterMirror);
    ASSERT_EQUAL(ResultAfterDecoderMirror, TestString); //Не проходит, никак не могу понять почему: Assertion failed

    encoder.SetEncodeAlgorithm("Multiply41");
    std::string ResultAfterMultiply41 = encoder.encode(TestString);
    std::string ResultAfterDecoderMultiply41 = encoder.decode(ResultAfterMultiply41);
    ASSERT_EQUAL(ResultAfterDecoderMultiply41, TestString);

    encoder.SetEncodeAlgorithm("ROT3");
    std::string ResultAfterROT3 = encoder.encode(TestString);
    std::string ResultAfterDecoderROT3 = encoder.decode(ResultAfterROT3);
    ASSERT_EQUAL(ResultAfterDecoderROT3, TestString);

}
