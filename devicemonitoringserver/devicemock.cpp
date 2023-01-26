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
    std::cout<< message;
    std::string decodeMessage = messageEncoder->decode(message);
    MessageSerializator::MessageStruct res =  MessageSerializator::deserialize(message);
    if (res.errorCode > 100)
        return;
    messageList.push_back(res.type);
    // TODO: Разобрать std::string, прочитать команду,
    // записать ее в список полученных комманд
    sendNextMeterage(); // Отправляем следующее измерение
}



void DeviceMock::onConnected()
{
    messageList = {};
    // TODO, если нужно
}

void DeviceMock::onDisconnected()
{
    messageList.clear();

}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
}

void DeviceMock::startMeterageSending()
{
    messageEncoder->chooseAlgorithm("Mirror");
    sendNextMeterage();
}

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size())
        return;
    const auto meterage = m_meterages.at(m_timeStamp);
    (void)meterage;
    ++m_timeStamp;
    std::string message = MessageSerializator::serialize(MessageSerializator::Meterage, -1, m_timeStamp, meterage);
    std::string encodeMessage = messageEncoder->encode(message);
    std::cout << message << "  ";
    std::cout << encodeMessage << "  ";
    sendMessage(encodeMessage);
}
