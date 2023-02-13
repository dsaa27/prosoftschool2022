#include "devicemonitoringserver.h"
#include "serialization/MessageSerializator.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <handlers/abstractnewconnectionhandler.h>
#include <server/abstractconnection.h>
#include <servermock/connectionservermock.h>
#include <optional>
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
    delete m_connectionServer;
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& deviceWorkSchedule)
{
    m_commandCenter.addDevice(deviceWorkSchedule);
}

bool DeviceMonitoringServer::chooseEncodingAlgorithm(const std::string &name)
{
    return m_encoder.chooseAlgorithm(name);
}

bool DeviceMonitoringServer::registerEncodingAlgorithm(BaseEncoderExecutor *algorithm)
{
    return m_encoder.addAlgorithm(algorithm);
}

double DeviceMonitoringServer::getStandardDeviation(uint64_t deviceId) {
    return m_commandCenter.getStandardDeviation(deviceId);
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
    std::optional<std::string> decodedMessage = m_encoder.decode(message);
    if (!decodedMessage)
        return;
    MessageSerializator::MessageStruct result = m_serializator.deserialize(*decodedMessage);
    Phase currentPhase = result.phase;
    CommandCenter::CheckResult checkResult = m_commandCenter.checkMeterageInPhase(currentPhase, deviceId);

    MessageSerializator::MessageStruct newMessage;
    std::string serializedMessage;

    if (checkResult.errorCode == CommandCenter::errorType::NoError)
    {
        newMessage.valueToCorrect = checkResult.valueToCorrect;
        newMessage.type = MessageSerializator::messageType::Command;
        serializedMessage = m_serializator.serialize(newMessage);
    }
    else
    {
        newMessage.type = MessageSerializator::messageType::Error;
        newMessage.errorCode = checkResult.errorCode;
        serializedMessage = m_serializator.serialize(newMessage);
    }
    std::optional<std::string> newEncodeMessage = m_encoder.encode(serializedMessage);
    if (newEncodeMessage)
        sendMessage(deviceId, *newEncodeMessage);
}

void DeviceMonitoringServer::onDisconnected(uint64_t clientId)
{
    m_commandCenter.deleteDevice(clientId);
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
