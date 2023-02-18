#include "devicemock.h"
#include "devicemockerrors.h"
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

    if(!m_encoder.setAlgorithm("Mirror"))
    {
        DeviceMockErrors::SET_ALGORITHM_ERROR.throwRunTimeError("Mirror");
    }
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
        DeviceMockErrors::DECODE_ERROR.throwRunTimeError(message);
    }
    MessageDto messageDto;
    if(!m_serializer.deserialize(decodedMessage, messageDto))
    {
        DeviceMockErrors::DESERIALIZE_ERROR.throwRunTimeError(decodedMessage);
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
            DeviceMockErrors::MESSAGE_TYPE_ERROR.throwRunTimeError(
                        std::to_string(messageDto.messageType));
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
        DeviceMockErrors::SERIALIZE_ERROR.throwRunTimeError("");
    }
    std::string encodedMessage;
    if(!m_encoder.encode(message, encodedMessage))
    {
        DeviceMockErrors::ENCODE_ERROR.throwRunTimeError(message);
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
