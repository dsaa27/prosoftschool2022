#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include "clientconnectionmock.h"
#include "connectionservermock.h"
#include "taskqueue.h"
#include "deviceworkschedule.h"
#include "MessageEncoder.h"

void monitoringServerTest1()
{
	TaskQueue taskQueue;
	DeviceMock device(new ClientConnectionMock(taskQueue));
	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId = 111;
	const uint64_t serverId = 11;
	ASSERT(device.bind(deviceId));
	ASSERT(server.listen(serverId));
	ASSERT(device.connectToServer(serverId));
	std::vector<uint8_t> meterag = {45, 33};
	std::vector <Phase> phase;
	for (uint64_t i = 1; i < meterag.size()+1; i++)
	{
		Phase onePhase;
		onePhase.timeStamp = i;
		onePhase.value = meterag[i-1] + 10;
		phase.push_back(onePhase);
	}
	DeviceWorkSchedule const devShedule = { deviceId, phase };
	device.setMeterages(meterag);
	server.setDeviceWorkSchedule(devShedule);
	std::vector <std::string> expected = { "55", "43" };
	device.setEncodingAlgoritm("ROT3");
	server.setEncodingAlgoritm("ROT3");
	while (taskQueue.processTask())
		;
	device.startMeterageSending();
	while (taskQueue.processTask())
		;
	std::vector <std::string> comList = device.getCommList();
	if (comList.size() != expected.size())
		ASSERT(false);
	for (int i = 0; i < comList.size(); i++)
	{
		ASSERT_EQUAL(comList[i], expected[i]);
	}
}
void monitoringServerTestErrorNoShedule()
{
	TaskQueue taskQueue;
	DeviceMock device(new ClientConnectionMock(taskQueue));
	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId = 111;
	const uint64_t serverId = 11;
	ASSERT(device.bind(deviceId));
	ASSERT(server.listen(serverId));
	ASSERT(device.connectToServer(serverId));
	std::vector<uint8_t> meterag = { 45};
	std::vector <Phase> phase = { {1, 17}};
	DeviceWorkSchedule const devShedule = {115, phase};
	device.setMeterages(meterag);
	server.setDeviceWorkSchedule(devShedule);
	std::vector <std::string> expected = { "NoSchedule"};
	device.setEncodingAlgoritm("ROT3");
	server.setEncodingAlgoritm("ROT3");
	while (taskQueue.processTask())
		;
	device.startMeterageSending();
	while (taskQueue.processTask())
		;
	std::vector <std::string> comList = device.getCommList();
	if (comList.size() != expected.size())
		ASSERT(false);
	for (int i = 0; i < comList.size(); i++)
	{
		ASSERT_EQUAL(comList[i], expected[i]);
	}
}
void monitoringServerTestErrorNoTimestamp()
{
	TaskQueue taskQueue;
	DeviceMock device(new ClientConnectionMock(taskQueue));
	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId = 111;
	const uint64_t serverId = 11;
	ASSERT(device.bind(deviceId));
	ASSERT(server.listen(serverId));
	ASSERT(device.connectToServer(serverId));
	std::vector<uint8_t> meterag = { 45, 56, 13, 77, 64};
	std::vector <Phase> phase = { {1, 17}, {2, 60}, {3, 45}, {4, 55}};
	DeviceWorkSchedule const devShedule = { 111, phase };
	device.setMeterages(meterag);
	server.setDeviceWorkSchedule(devShedule);
	std::vector <std::string> expected = { "17", "60", "45", "55", "NoTimestamp"};
	device.setEncodingAlgoritm("Mirror");
	server.setEncodingAlgoritm("Mirror");
	while (taskQueue.processTask())
		;
	device.startMeterageSending();
	while (taskQueue.processTask())
		;
	std::vector <std::string> comList = device.getCommList();
	if (comList.size() != expected.size())
		ASSERT(false);
	for (int i = 0; i < comList.size(); i++)
	{
		ASSERT_EQUAL(comList[i], expected[i]);
	}
}
void monitoringServerTestErrorObsole()
{
	TaskQueue taskQueue;
	DeviceMock device(new ClientConnectionMock(taskQueue));
	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId = 111;
	const uint64_t serverId = 11;
	ASSERT(device.bind(deviceId));
	ASSERT(server.listen(serverId));
	ASSERT(device.connectToServer(serverId));
	std::vector<uint8_t> meterag = { 100, 24, 78, 4, 64 };
	std::vector <Phase> phase = { {1, 34}, {2, 78}, {3, 45}, {4, 21}, {6, 97} };
	DeviceWorkSchedule const devShedule = { 111, phase };
	device.setMeterages(meterag);
	server.setDeviceWorkSchedule(devShedule);
	std::vector <std::string> expected = { "34", "78", "45", "21", "Obsole" };
	device.setEncodingAlgoritm("Multiply41");
	server.setEncodingAlgoritm("Multiply41");
	while (taskQueue.processTask())
		;
	device.startMeterageSending();
	while (taskQueue.processTask())
		;
	std::vector <std::string> comList = device.getCommList();
	if (comList.size() != expected.size())
		ASSERT(false);
	for (int i = 0; i < comList.size(); i++)
	{
		ASSERT_EQUAL(comList[i], expected[i]);
	}
}
