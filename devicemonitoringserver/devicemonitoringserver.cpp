#include "devicemonitoringserver.h"
#include "handlers/abstractaction.h"
#include "handlers/abstractmessagehandler.h"
#include "handlers/abstractnewconnectionhandler.h"
#include "message/message.hxx"
#include "server/abstractconnection.h"
#include "servermock/connectionservermock.h"
#include "servermock/connectionservermock.h"

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

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& schedule)
{
    _comcen.add(schedule);
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
    const std::string decoded_msg{_menc.decode(message)};
    const std::unique_ptr<const dms::message::message> deser_msg{
        _ser.deserialize(decoded_msg)};

    if (deser_msg->type() == dms::message::MSG_TYPE::METERAGE) {
        const auto meterage = dynamic_cast<const dms::message::meterage*>(deser_msg.get());

        if (nullptr == meterage) {
            return;
        }

        const std::unique_ptr<const dms::message::message> ret_msg{
            _comcen.check(deviceId, *meterage)};

        const std::string ser_msg{_ser.serialize(ret_msg)};
        const std::string encoded_msg{_menc.decode(ser_msg)};

        sendMessage(deviceId, encoded_msg);
    }
}

void DeviceMonitoringServer::onDisconnected(uint64_t clientId)
{
    _comcen.rem(clientId);
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
