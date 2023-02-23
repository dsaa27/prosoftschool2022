#include "devicemonitoringserver.h"
#include "devicemonitoringservererrors.h"
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

    if(!m_encoder.setAlgorithm("Mirror"))
    {
        std::cerr << DeviceMonitoringServerErrors::SET_ALGORITHM_ERROR.formatString("Mirror") << std::endl;
    }
}

DeviceMonitoringServer::~DeviceMonitoringServer()
{
    delete m_connectionServer;
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& deviceWorkSchedule)
{
    if(!m_commandCenter.addDeviceWorkShedule(new DeviceWorkSchedule(deviceWorkSchedule)))
    {
        std::cerr << DeviceMonitoringServerErrors::SET_SCHEDULE_ERROR.formatString(
                         std::to_string(deviceWorkSchedule.deviceId))
                  << std::endl;
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
        return;
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
            std::cerr << DeviceMonitoringServerErrors::CONTROL_ERROR.formatString(
                             std::to_string(control.errorType))
                      << std::endl;
            return;
    }
    std::string encodedMessage;
    if(!convertToEncodedMessage(messageResult, encodedMessage))
        return;
    sendMessage(deviceId, encodedMessage);
}

void DeviceMonitoringServer::onDisconnected(uint64_t /*clientId*/)
{

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
    {
        std::cerr << DeviceMonitoringServerErrors::DECODE_ERROR.formatString(encodedMessage) << std::endl;
        return false;
    }
    if(!m_serializer.deserialize(decodedMessage, messageDto))
    {
        std::cerr << DeviceMonitoringServerErrors::DESERIALIZE_ERROR.formatString(decodedMessage) << std::endl;
        return false;
    }
    return true;
}

bool DeviceMonitoringServer::convertToEncodedMessage(const MessageDto& messageDto, std::string& encodedMessage) const
{
    std::string strMessage;
    if(!m_serializer.serialize(messageDto, strMessage))
    {
        std::cerr << DeviceMonitoringServerErrors::SERIALIZE_ERROR.formatString("") << std::endl;
        return false;
    }
    if(!m_encoder.encode(strMessage, encodedMessage))
    {
        std::cerr << DeviceMonitoringServerErrors::ENCODE_ERROR.formatString(strMessage) << std::endl;
        return false;
    }
    return true;
}
