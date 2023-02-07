#include "devicemonitoringserver.h"
#include "serialization/MessageSerializator.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <handlers/abstractnewconnectionhandler.h>
#include <server/abstractconnection.h>
#include <servermock/connectionservermock.h>
#include <vector>

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
    delete commandCenter;
    delete serializator;
    delete m_connectionServer;
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& deviceWorkSchedule)
{
    commandCenter->addDevice(deviceWorkSchedule);
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

void DeviceMonitoringServer::onMessageReceived(uint64_t deviceId, const std::string& message)
{
    MessageEncoder* messageEncoder = encoder->getDeviceEncoder(deviceId);
    if (messageEncoder == nullptr)
        return;

    std::string decodeMessage = messageEncoder->decode(message);
    MessageSerializator::MessageStruct result = serializator->deserialize(decodeMessage);

    Phase currentPhase = result.phase;
    int64_t valueToCorrect = commandCenter->checkMeterageInPhase(currentPhase, deviceId);

    MessageSerializator::MessageStruct newMessage;
    std::string serializedMessage;
    if (valueToCorrect <= 100)
    {
        newMessage.valueToCorrect = valueToCorrect;
        newMessage.type = MessageSerializator::Command;
        serializedMessage = serializator->serialize(newMessage);
    }
    else
    {
        newMessage.type = MessageSerializator::Error;
        newMessage.errorCode = valueToCorrect;
        serializedMessage = serializator->serialize(newMessage);
    }
    std::string newEncodeMessage = messageEncoder->encode(serializedMessage);
    sendMessage(deviceId, newEncodeMessage);
}

void DeviceMonitoringServer::onDisconnected(uint64_t clientId)
{
    encoder->deleteDevice(clientId);
    commandCenter->deleteDevice(clientId);
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

double DeviceMonitoringServer::getStandardDeviation(uint64_t deviceId) {
    return commandCenter->getStandardDeviation(deviceId);
}
