#include "devicemock.h"
#include "handlers/abstractaction.h"
#include "handlers/abstractmessagehandler.h"
#include "server/abstractclientconnection.h"
#include "message.h"
#include "messageencoder.h"
#include <sstream>

DeviceMock::DeviceMock(AbstractClientConnection* clientConnection, std::vector<std::string>& messages) :
    m_clientConnection(clientConnection), m_messagesFromServer(messages)
{
    struct ConnectedHandler : public AbstractAction
    {
    public:
        ConnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onConnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setConnectedHandler(new ConnectedHandler(this));

    struct DisconnectedHandler : public AbstractAction
    {
    public:
        DisconnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onDisconnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setDisconnectedHandler(new DisconnectedHandler(this));

    struct MessageHandler : public AbstractMessageHandler
    {
        MessageHandler(DeviceMock* client) :
            m_client(client) {}

    private:
        void operator()(const std::string& message) final
        {
            m_client->onMessageReceived(message);
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setMessageHandler(new MessageHandler(this));
	
	auto* messageSerializator = new MessageSerializator;
    m_serializator = messageSerializator;
    auto* messageEncoder = new MessageEncoder;
    m_encoder = messageEncoder;
}

DeviceMock::~DeviceMock()
{
    delete m_clientConnection;
	delete m_serializator;
    delete m_encoder;
}

bool DeviceMock::bind(uint64_t deviceId)
{
    return m_clientConnection->bind(deviceId);
}

bool DeviceMock::connectToServer(uint64_t serverId)
{
    return m_clientConnection->connectToHost(serverId);
}

void DeviceMock::sendMessage(const std::string& message) const
{
    m_clientConnection->sendMessage(message);
}

void DeviceMock::onMessageReceived(const std::string& message)
{
    std::string deencodedSerializedMsg = m_encoder->proceedDecoding(message);
    const auto* commandFromServer = m_serializator->deserialize(deencodedSerializedMsg);
    std::ostringstream toCommandsList;
    if (const auto* command = dynamic_cast<const Command*>(commandFromServer)) {
        if (command->m_up == true) {
            toCommandsList << "Increase by " << std::to_string(command->m_value) << " points";
            m_messagesFromServer.push_back(toCommandsList.str());
        } else {
            toCommandsList << "Decrease by " << std::to_string(command->m_value) << " points";
            m_messagesFromServer.push_back(toCommandsList.str());
        }
    } else if (const auto* error = dynamic_cast<const Error*>(commandFromServer)) {
        if (error->m_errType == Error::NoSchedule) {
            toCommandsList << "Error at timestamp " << std::to_string(m_timeStamp - 1) << ": no such schedule";
            m_messagesFromServer.push_back(toCommandsList.str());
        } else if (error->m_errType == Error::NoTimestamp) {
            toCommandsList << "Error at timestamp " << std::to_string(m_timeStamp - 1) << ": no timestamp";
            m_messagesFromServer.push_back(toCommandsList.str());
        } else if (error->m_errType == Error::Obsolete) {
            toCommandsList << "Error at timestamp " << std::to_string(m_timeStamp - 1) << ": obsolete timestamp";
            m_messagesFromServer.push_back(toCommandsList.str());
        }
    } else if (const auto* info = dynamic_cast<const Info*>(commandFromServer)) {
        m_messagesFromServer.push_back(info->m_message);
    } else {
        m_messagesFromServer.push_back(message);
    }
    sendNextMeterage();

	delete commandFromServer;
}

void DeviceMock::onConnected()
{
    std::ostringstream buffer;
    buffer << "Device ID " << m_clientConnection->bindedId() << " connected";
    Info info{buffer.str()};
    std::string serializedInfo = m_serializator->serialize(&info);
    std::string encodedSerializedInfo = m_encoder->proceedEncoding(serializedInfo);
    sendMessage(encodedSerializedInfo);
}

void DeviceMock::onDisconnected()
{
    std::ostringstream buffer;
    buffer << "Device ID " << m_clientConnection->bindedId() << " disconnected";
    Info info{buffer.str()};
    std::string serializedInfo = m_serializator->serialize(&info);
    std::string encodedSerializedInfo = m_encoder->proceedEncoding(serializedInfo);
    sendMessage(encodedSerializedInfo);
}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
}

void DeviceMock::startMeterageSending()
{
    sendNextMeterage();
}

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size())
        return;
    /*if (m_timeStamp == 8 && obsoleteErrorFlag)
        return;*/
	const auto meterage = m_meterages.at(m_timeStamp);
    Meterage currentMeterage{meterage, m_timeStamp};
    std::string encodedSerializedMsg = m_encoder->proceedEncoding(m_serializator->serialize(&currentMeterage));
    sendMessage(encodedSerializedMsg);
    ++m_timeStamp;
    
	/*if (m_timeStamp == 9) {
        m_timeStamp = 7;
        obsoleteErrorFlag = true;
    }*/
}

void DeviceMock::setEncodingMethod(const std::string& name) {
    m_encoder->selectMethod(name);
}

void DeviceMock::registerСustomEncodingMethod(const std::string& name, const std::string& key) {
    m_encoder->registerСustom(name, key);
}

std::string DeviceMock::getEncodingMethodName() const {
    return m_encoder->getName();
}

void DeviceMock::disconnect() {
    if (m_clientConnection) {
        onDisconnected();
        m_clientConnection->disconnect();
    }
}
