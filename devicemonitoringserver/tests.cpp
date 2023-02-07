#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "encoder/messageencoder.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include "messageSerializator.h"
#include "encoder/rot4.h"
#include <cstdlib>

/*!
 * \brief Генератор псевдослучайных чисел в заданном диапазоне
 */
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
/*!
 * \brief Сгенерировать случайные измерения
 */
std::vector<uint8_t> generateMeterages(uint64_t maxTime)
{
    std::srand(0);
    std::vector<uint8_t> meterages;
    for (uint64_t i = 0; i <= maxTime; i++)
    {
        uint8_t x = getRandomNumber(0, 100);
        meterages.push_back(x);
    }
    return meterages;
}
/*!
 * \brief Сгенерировать ожидаемые ответы от сервера на основе расписания
 */
std::vector<int> generateExpected(const std::vector<uint8_t>& meterages, std::vector<Phase> schedule)
{
    std::vector<int> expected;
    uint64_t j = 0;
    uint64_t i = 0;
    int adj;
    for (; i < schedule.size(); i++)
    {
        for (; j < schedule[i].timeStamp; j++)
        {
            adj = schedule[i - 1].value - meterages[j];
            expected.push_back(adj);
        }
        j = schedule[i].timeStamp;
    }
    adj = schedule[i-1].value - meterages[j];
    expected.push_back(adj);

    return  expected;
}

void monitoringServerTest()
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

    std::vector<Phase> schedule = {{0,10},
                                   {10, 50},
                                   {200, 30},
                                   {300, 70},
                                   {400, 90},
                                   {500, 100}
                                  };
    std::vector<uint8_t> meterages = generateMeterages(500);
    std::vector<int> expected = generateExpected(meterages, schedule);
    device.setMeterages(meterages);

    DeviceWorkSchedule deviceSchedule;
    deviceSchedule.deviceId = 111;
    deviceSchedule.schedule = schedule;
    server.setDeviceWorkSchedule(deviceSchedule);

    taskQueue.processTask(); //выполняем задачу установления соединения
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;

    std::vector<int> responce = device.responces();
    uint64_t responceSize = responce.size();
    uint64_t expectedSize = expected.size();
    ASSERT_EQUAL(responceSize, expectedSize);
    ASSERT_EQUAL(responce, expected);
}

void serializatorTest()
{
    MessageSerializer ser;
    std::vector<std::string> stringsToTest = {
        "05:10",
        "0111:222",
        "0557:1",
        "11",
        "155",
        "21",
        "22",
        "23"
    };
    while (!stringsToTest.empty())
    {

        std::string serialMessage1 = stringsToTest.back();
        stringsToTest.pop_back();
        std::string serialMessage2 = "";
        MessageStruct message = ser.deSerializate(serialMessage1);
        serialMessage2 = ser.serializate(message);
        ASSERT_EQUAL(serialMessage1, serialMessage2);
    }
}

void encoderTest()
{
    MessageEncoder en;
    en.setEncodeAlgorithm("ROT3");
    std::string message = "Hello!123";
    std::string encodedMessage = en.encode(message);
    std::string decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "1";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "My encoder works perfect. Let's check it: 1234567890-=!@#$%^&*()_+";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);

    en.setEncodeAlgorithm("Mirror");
    message = "Hello!123";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "1";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "My encoder works perfect. Let's check it: 1234567890-=!@#$%^&*()_+";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);

    en.setEncodeAlgorithm("Multiply41");
    message = "Hello!123";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "1";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "My encoder works perfect. Let's check it: 1234567890-=!@#$%^&*()_+";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);

    Rot4 rot4;
    en.registerNewAlgorithm(rot4);
    en.setEncodeAlgorithm("ROT4");
    message = "Hello!123";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "1";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
    message = "My encoder works perfect. Let's check it: 1234567890-=!@#$%^&*()_+";
    encodedMessage = en.encode(message);
    decodedMessage = en.decode(encodedMessage);
    ASSERT_EQUAL(message, decodedMessage);
}

void comandCenterTest()
{
    CommandCenter cc;
    MessageStruct message;
    message.messageType = METERAGE;
    message.measurements = {0, 15};
    MessageStruct answer;
    answer = cc.generateCommand(64, message);
    ASSERT_EQUAL(answer.messageType, ERROR);
    ASSERT_EQUAL(answer.errorType, NO_SCHEDULE);

    std::vector<Phase> schedule = {{0,10},
                                  {100, 50},
                                  {200, 40}
                                  };
    DeviceWorkSchedule schedule64 = {64, schedule};
    cc.setSchedule(schedule64);
    message.measurements = {0, 15};
    answer = cc.generateCommand(64, message);
    ASSERT_EQUAL(answer.messageType, COMMAND);
    ASSERT_EQUAL(answer.adjustment, -5);
    ASSERT_EQUAL(cc.getMse(64), 5);

    message.measurements = {105, 40};
    answer = cc.generateCommand(64, message);
    ASSERT_EQUAL(answer.messageType, COMMAND);
    ASSERT_EQUAL(answer.adjustment, 10);
    float expectedMse = std::sqrt((pow(5, 2)+pow(10, 2))/2.0);
    ASSERT_EQUAL(cc.getMse(64), expectedMse);

    message.measurements = {100, 40};
    answer = cc.generateCommand(64, message);
    ASSERT_EQUAL(answer.messageType, ERROR);
    ASSERT_EQUAL(answer.errorType, OBSOLETE);

    message.measurements = {200, 40};
    answer = cc.generateCommand(64, message);
    ASSERT_EQUAL(answer.messageType, COMMAND);
    ASSERT_EQUAL(answer.adjustment, 0);
    expectedMse = std::sqrt((pow(5, 2)+pow(10, 2))/3.0);
    ASSERT_EQUAL(cc.getMse(64), expectedMse);

    message.measurements = {201, 40};
    answer = cc.generateCommand(64, message);
    ASSERT_EQUAL(answer.messageType, ERROR);
    ASSERT_EQUAL(answer.errorType, NO_TIMESTAMP);
}
