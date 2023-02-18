#include "devicemonitoringserver.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <handlers/abstractnewconnectionhandler.h>
#include <server/abstractconnection.h>
#include <servermock/connectionservermock.h>

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

    m_encoder.setAlgorithm("Mirror");
}

DeviceMonitoringServer::~DeviceMonitoringServer()
{
    delete m_connectionServer;
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& deviceWorkSchedule)
{
    if(m_commandCenter.addDeviceWorkShedule(new DeviceWorkSchedule(deviceWorkSchedule)))
    {
        m_connectedDevices.insert(std::make_pair(deviceWorkSchedule.deviceId, true));
    }
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
    MessageDto messageDto;
    if(!convertToMessageDto(message, messageDto))
    {
        std::cerr << "[Server] Error converting to MessageDto: " << message << std::endl;
        return;
    }
    Control control = m_commandCenter.checkDeviceWorkShedule(deviceId, messageDto.meterage);
    MessageDto messageResult;
    switch (control.errorType)
    {
        case ErrorType::eUnknown:
            messageResult.messageType = MessageType::eCommand;
            messageResult.parameterTuning = control.parameterTuning;
            break;
        case ErrorType::eNoSchedule:
        case ErrorType::eNoTimestamp:
        case ErrorType::eObsolete:
            messageResult.messageType = MessageType::eError;
            messageResult.errorType = control.errorType;
            break;
        default:
            std::cerr << "[Server] Unexpected ErrorType: " << control.errorType << std::endl;
            return;
    }
    std::string encodedMessage;
    if(!convertToEncodedMessage(messageResult, encodedMessage))
        std::cerr << "[Server] Error converting to string: " << encodedMessage << std::endl;
    sendMessage(deviceId, encodedMessage);
}

void DeviceMonitoringServer::onDisconnected(uint64_t clientId)
{
    if(m_connectedDevices.find(clientId) != m_connectedDevices.end())
        m_connectedDevices.at(clientId) = false;
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

std::vector<PhaseStatistics> DeviceMonitoringServer::getDeviceStatistics(uint64_t deviceId) const
{
    return m_commandCenter.getDeviceStatistics(deviceId);
}

bool DeviceMonitoringServer::convertToMessageDto(const std::string& encodedMessage, MessageDto& messageDto) const
{
    std::string decodedMessage;
    if(!m_encoder.decode(encodedMessage, decodedMessage))
        return false;
    return m_serializer.deserialize(decodedMessage, messageDto);
}

bool DeviceMonitoringServer::convertToEncodedMessage(const MessageDto& messageDto, std::string& encodedMessage) const
{
    std::string strMessage;
    if(!m_serializer.serialize(messageDto, strMessage))
        return false;
    return m_encoder.encode(strMessage, encodedMessage);
}
