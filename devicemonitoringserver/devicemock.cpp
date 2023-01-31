#include "devicemock.h"
#include "serialization/MessageSerializator.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <server/abstractclientconnection.h>
#include <sstream>
#include <iostream>

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
    MessageEncoder* messageEncoder = encoder->getDeviceEncoder(m_clientConnection->bindedId());
    std::cout<< " " << message << "; ";
    std::string decodeMessage = messageEncoder->decode(message);
    MessageSerializator::MessageStruct res =  serializator->deserialize(decodeMessage);
    responses.push_back(decodeMessage);
    if (res.errorCode > 100)
        std::cout<< "error; ";
    receivedCommands.push_back(res.type);
    sendNextMeterage(); // Отправляем следующее измерение
}



void DeviceMock::onConnected()
{
    receivedCommands = {};
}

void DeviceMock::onDisconnected()
{
    delete encoder->getDeviceEncoder(m_clientConnection->bindedId());
    receivedCommands.clear();
}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
}

void DeviceMock::startMeterageSending()
{
    encoder->getDeviceEncoder(m_clientConnection->bindedId())->chooseAlgorithm("ROT3");
    sendNextMeterage();
}

void DeviceMock::sendNextMeterage()
{
    MessageEncoder* messageEncoder = encoder->getDeviceEncoder(m_clientConnection->bindedId());
    if (m_timeStamp >= m_meterages.size())
        return;
    const auto meterage = m_meterages.at(m_timeStamp);
    (void)meterage;
    ++m_timeStamp;
    std::string message = serializator->serialize(MessageSerializator::Meterage, -1, m_timeStamp, meterage);
    std::string encodeMessage = messageEncoder->encode(message);
    std::cout << message << "; ";
    sendMessage(encodeMessage);
}

std::vector<std::string> DeviceMock::getResponses() {
    return responses;
}

