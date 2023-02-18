#include "devicemock.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <server/abstractclientconnection.h>

DeviceMock::DeviceMock(AbstractClientConnection* clientConnection) :
    m_clientConnection(clientConnection)
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

    m_encoder.setAlgorithm("Mirror");
}

DeviceMock::~DeviceMock()
{
    delete m_clientConnection;
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
    std::string decodedMessage;
    if(!m_encoder.decode(message, decodedMessage))
    {
        std::cerr << "(Device) Decoded error: " << message << std::endl;
        return;
    }
    MessageDto messageDto;
    if(!m_serializer.deserialize(decodedMessage, messageDto))
    {
        std::cerr << "(Device) Deserialize error: " << message << std::endl;
        return;
    }
    switch(messageDto.messageType)
    {
        case MessageType::eCommand:
            m_receivedValues.push_back(messageDto.parameterTuning);
            //NOTE: without break
        case MessageType::eError:
        case MessageType::eMeterage:
            m_messageTypes.push_back(messageDto.messageType);
            break;
        default:
            std::cerr << "(Device) Unexpected message type: " << messageDto.messageType << std::endl;
            return;
    }
    sendNextMeterage();
}

void DeviceMock::onConnected()
{
    // TODO, если нужно
}

void DeviceMock::onDisconnected()
{
    // TODO, если нужно
}

void DeviceMock::setMeterages(std::vector<Meterage> meterages)
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
    MessageDto messageDto;
    messageDto.messageType = MessageType::eMeterage;
    messageDto.meterage = m_meterages.at(m_timeStamp);
    std::string message;
    if(!m_serializer.serialize(messageDto, message))
    {
        std::cerr << "(Device) Serialize error: " << message << std::endl;
        return;
    }
    std::string encodedMessage;
    if(!m_encoder.encode(message, encodedMessage))
    {
        std::cerr << "(Device) Encoded error: " << message << std::endl;
        return;
    }
    ++m_timeStamp;
    sendMessage(encodedMessage);
}

std::vector<MessageType> DeviceMock::getReceivedMessageTypes() const
{
    return std::vector<MessageType>(m_messageTypes);
}

std::vector<int64_t> DeviceMock::getReceivedValues() const
{
    return std::vector<int64_t>(m_receivedValues);
}
