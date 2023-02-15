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

    m_serial = new MessageSerialiser;

    m_encoder = new MessageEncoder;
}

DeviceMock::~DeviceMock()
{
    delete m_clientConnection;

    delete m_serial;
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
    std::string BufferMessage = message;

    std::string Message = m_encoder->decode(BufferMessage);
    std::string TypeOfMessage = m_serial->GetTypeMessage(Message);

    if (TypeOfMessage == "Command")
    {
        m_CommandFromServer.push_back(m_serial->GetCommand(Message));

        double u_buffermeterages = static_cast <double> (m_meterages.at(m_cout_of_meterages));

        u_buffermeterages = u_buffermeterages + m_CommandFromServer.at(m_cout_of_meterages);

        m_meterages.at(m_cout_of_meterages) = static_cast <uint8_t> (u_buffermeterages);

        m_cout_of_meterages++;
    }
    else
    {
        std::cout << "This is Error: " << m_serial->GetTypeError(Message);
    }

    sendNextMeterage(); // Отправляем следующее измерение

}

void DeviceMock::onConnected()
{

}

void DeviceMock::onDisconnected()
{

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
    const auto meterage = m_meterages.at(m_timeStamp);
    (void)meterage;

    std::string Message = m_serial->serialize_Message(meterage,m_timeStamp);

    Message = m_encoder->encode(Message);

    sendMessage(Message);

    ++m_timeStamp;
}

void DeviceMock::setEncodingAlgoritm(BaseEncoderExecutor* EncodeAlgoritm)
{
    m_encoder->registration_algorithm(EncodeAlgoritm);
}

std::vector <double> DeviceMock::responce() const
{
    return m_CommandFromServer;
}

