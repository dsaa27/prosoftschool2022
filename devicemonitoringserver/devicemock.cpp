#include "devicemock.h"
#include "handlers/abstractaction.h"
#include "handlers/abstractmessagehandler.h"
#include "server/abstractclientconnection.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#include <variant>
#include "MessageSerializerDev.h"
#include "MessageEncoder.h"

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

    std::string decodedMess = oEncode.decode(message);
    std::string deserialMess = MessageSerializer::deserialization(decodedMess);
    commandList.push_back(deserialMess);
    sendNextMeterage();
}

void DeviceMock::onConnected()
{
    std::cout << "connected";
}

void DeviceMock::onDisconnected()
{
    // TODO, если нужно
}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
}

void DeviceMock::startMeterageSending()
{
    sendNextMeterage();
}
void DeviceMock::setEncodingAlgoritm(std::string name)
{
    oEncode.algChosser(name);
}
void DeviceMock::regNewAlgoritm(std::string name, BaseEncoderExecutor *executor)
{
    oEncode.algRegistr(name, executor);
}

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size())
        return;
    const auto meterage = m_meterages.at(m_timeStamp);
    ++m_timeStamp;
    (void)meterage;
    MessageSerializer message(meterage, m_timeStamp);
    std::string serial_Message = message.serialization(meterage, m_timeStamp);
    std::string encoded_Message = oEncode.encode(serial_Message);
    std::string *mesToSend = &encoded_Message;
    if (encoded_Message.length() != 0)
    {
        sendMessage(*mesToSend);
    }
    
}
std::vector<std::string> DeviceMock::getCommList()
{
    return commandList;
}
