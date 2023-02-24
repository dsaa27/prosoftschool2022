#include "devicemonitoringserver.h"
#include "deviceworkschedule.h"
#include "commandcenter.h"
#include "message.h"
#include "handlers/abstractaction.h"
#include "handlers/abstractmessagehandler.h"
#include "handlers/abstractnewconnectionhandler.h"
#include "server/abstractconnection.h"
#include "servermock/connectionservermock.h"
#include <sstream>
#include <iostream>

DeviceMonitoringServer::DeviceMonitoringServer(AbstractConnectionServer* connectionServer,
std::unordered_map<uint64_t, std::vector<std::string>&>& messages) :
    m_connectionServer(connectionServer), m_messagesFromClients(messages)
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
	
	auto* commandCenter = new CommandCenter;
    m_commandcenter = commandCenter;
    auto* messageSerializator = new MessageSerializator;
    m_serializator = messageSerializator;
    auto* messageEncoder = new MessageEncoder;
    m_encoder = messageEncoder;
}

DeviceMonitoringServer::~DeviceMonitoringServer()
{
    delete m_connectionServer;
	delete m_commandcenter;
    delete m_serializator;
    delete m_encoder;
    /*по-хорошему, публичного доступа к сообщениям от клиентов быть не должно,
    потому в методе onMessageReceived, если зарегистрированного в мапе m_messagesFromClients
    клиента нет, мы создаем в куче новые векторы из строк и инициализируемся указателями на них
    В деструкторе, соответственно, мы пробегаемся по указателям на созданные вектора и удаляем их
    Но поскольку для тестирования нам нужно видеть, что посылают устройства, и
    мы сами на стеке создаем нужные векторы из строк и инициализируемся ими, - чтобы не вызывался
    оператор delete, пришлось закомментировать участок кода
    */
    /*if (m_messagesFromClients.size() != 0) {
        for (const auto& it : m_messagesFromClients) {
            delete &it.second;
        }
    }*/
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& workSchedule)
{
    m_commandcenter->setSchedule(workSchedule);
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
    if (m_messagesFromClients.count(deviceId) == 0) {
        std::vector<std::string>* messagesFromNewClient = new std::vector<std::string>;
        m_messagesFromClients.insert(std::pair<uint64_t, std::vector<std::string>&>(deviceId, *messagesFromNewClient));
    }

    std::string deencodedSerializedMsg = m_encoder->proceedDecoding(message);
    const auto* messageFromClient = m_serializator->deserialize(deencodedSerializedMsg);
    const auto& it = m_messagesFromClients.find(deviceId);
    if (dynamic_cast<const Meterage*>(messageFromClient)) {
        const auto* newCommand = m_commandcenter->makeDecision(deviceId, messageFromClient);
        std::string encodedSerializedMsg = m_encoder->proceedEncoding(m_serializator->serialize(newCommand));
        sendMessage(deviceId, encodedSerializedMsg);
    } else if (const auto* info = dynamic_cast<const Info*>(messageFromClient)) {
        it->second.push_back(info->m_message);
    } else {
        it->second.push_back(message);
    }

    delete messageFromClient;
}

double DeviceMonitoringServer::getMSE(uint64_t deviceId) {
    auto* conn = m_connectionServer->connection(deviceId);
    if (conn)
        return m_commandcenter->getMSE(deviceId);
    else
        return zero;
}

void DeviceMonitoringServer::onDisconnected(uint64_t deviceId)
{
    std::ostringstream buffer;
    buffer << "Server ID " << m_connectionServer->listenedId() << " disconnected";
    Info info{buffer.str()};
    std::string serializedInfo = m_serializator->serialize(&info);
    std::string encodedSerializedInfo = m_encoder->proceedEncoding(serializedInfo);
    sendMessage(deviceId, encodedSerializedInfo);
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

void DeviceMonitoringServer::setEncodingMethod(const std::string& name) {
    m_encoder->selectMethod(name);
}

void DeviceMonitoringServer::registerСustomEncodingMethod(const std::string& name, const std::string& key) {
    m_encoder->registerСustom(name, key);
}

std::string DeviceMonitoringServer::getEncodingMethodName() const {
    return m_encoder->getName();
}

void DeviceMonitoringServer::disconnect() {
    if (m_connectionServer) {
        for (const auto& conn : dynamic_cast<ConnectionServerMock*>(m_connectionServer)->m_connections) {
            onDisconnected(conn.first);
        }
        m_connectionServer->disconnect();
    }
}
