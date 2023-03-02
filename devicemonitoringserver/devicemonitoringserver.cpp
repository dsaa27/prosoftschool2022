#include "devicemonitoringserver.h"
#include "handlers/abstractaction.h"
#include "handlers/abstractmessagehandler.h"
#include "handlers/abstractnewconnectionhandler.h"
#include "server/abstractconnection.h"
#include "servermock/connectionservermock.h"

#include "ComandCenter.h"


DeviceMonitoringServer::DeviceMonitoringServer(AbstractConnectionServer* connectionServer) :
	m_connectionServer(connectionServer)
{
	struct NewConnectionHandler : public AbstractNewConnectionHandler
	{
	public:
		NewConnectionHandler(DeviceMonitoringServer* server) :
			m_server(server) {}
		void operator()(AbstractConnection* conn) final
		{
			m_server->onNewIncomingConnection(conn);
		}

	private:
		DeviceMonitoringServer* m_server = nullptr;
	};
	m_connectionServer->setNewConnectionHandler(new NewConnectionHandler(this));
}

DeviceMonitoringServer::~DeviceMonitoringServer()
{
	delete m_connectionServer;
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& DeviceWorkSchedule)
{
	oCmdCenter.plan = DeviceWorkSchedule;
}

bool DeviceMonitoringServer::listen(uint64_t serverId)
{
	return m_connectionServer->listen(serverId);
}

void DeviceMonitoringServer::sendMessage(uint64_t deviceId, const std::string& message)
{
	auto* conn = m_connectionServer->connection(deviceId);
	if (conn)
		conn->sendMessage(message);
}
void DeviceMonitoringServer::setEncodingAlgoritm(std::string name)
{

	oEncode.algChosser(name);
	oCmdCenter.setEncodingAlgoritm(name);
}
void DeviceMonitoringServer::regNewAlgoritm(std::string name, BaseEncoderExecutor *executor)
{
	
	oEncode.algRegistr(name, executor);
}
double DeviceMonitoringServer::get_sDeviation()
{
	return oCmdCenter.getSDeviation();
}

void DeviceMonitoringServer::onMessageReceived(uint64_t deviceId, const std::string& message)
{
	std::string encoded = oEncode.decode(message);
	MeterageMessage deserialized = MessageSerializer::deserialization(encoded);
	uint64_t timeStmp = deserialized.timeStamp;
	uint8_t metrage = deserialized.metrages;
	std::string messageToDev = oCmdCenter.comparisonWPlan(deviceId, timeStmp, metrage);
	sendMessage(deviceId, messageToDev);
}

void DeviceMonitoringServer::onDisconnected(uint64_t /*clientId*/)
{
	// TODO, если нужен
}

void DeviceMonitoringServer::onNewIncomingConnection(AbstractConnection* conn)
{
	addMessageHandler(conn);
	addDisconnectedHandler(conn);
}

void DeviceMonitoringServer::addMessageHandler(AbstractConnection* conn)
{
	struct MessageHandler : public AbstractMessageHandler
	{
		MessageHandler(DeviceMonitoringServer* server, uint64_t clientId) :
			m_server(server), m_clientId(clientId) {}

	private:
		void operator()(const std::string& message) final
		{
			m_server->onMessageReceived(m_clientId, message);
		}

	private:
		DeviceMonitoringServer* m_server = nullptr;
		uint64_t m_clientId = 0;
	};
	const auto clientId = conn->peerId();
	conn->setMessageHandler(new MessageHandler(this, clientId));
}

void DeviceMonitoringServer::addDisconnectedHandler(AbstractConnection* conn)
{
	struct DisconnectedHandler : public AbstractAction
	{
		DisconnectedHandler(DeviceMonitoringServer* server, uint64_t clientId) :
			m_server(server), m_clientId(clientId) {}

	private:
		void operator()() final
		{
			m_server->onDisconnected(m_clientId);
		}

	private:
		DeviceMonitoringServer* m_server = nullptr;
		uint64_t m_clientId = 0;
	};
	const auto clientId = conn->peerId();
	conn->setDisconnectedHandler(new DisconnectedHandler(this, clientId));
}
