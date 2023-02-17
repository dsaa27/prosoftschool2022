#include "devicemock.h"
#include "handlers/abstractaction.h"
#include "handlers/abstractmessagehandler.h"
#include "message/message.hxx"
#include "server/abstractclientconnection.h"
#include <memory>

#include <iostream>
using std::cout;
using std::endl;

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
    // TODO: Разобрать std::string, прочитать КОМАНДУ,
    // записать ее в список полученных команд

    const auto decoded_msg = _menc.decode(message);
    const auto deser_msg = _ser.deserialize(decoded_msg);

    if (deser_msg->type() == dms::message::MSG_TYPE::COMMAND) {
        const auto command =
            dynamic_cast<const dms::message::command*>(deser_msg.get());

        if (nullptr != command) {
            _commands.push_back(command->value());
        }
    }

    sendNextMeterage(); // Отправляем следующее измерение
}

void DeviceMock::onConnected()
{
    // TODO, если нужно
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

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size()) {
        return;
    }

    const auto meterage = m_meterages.at(m_timeStamp);

    // TODO: Сформировать std::string и передать в sendMessage
    cout << m_timeStamp << ' ' << int(meterage) << endl;

    const std::unique_ptr<const dms::message::message> msg{
        new const dms::message::meterage(m_timeStamp, meterage)};

    ++m_timeStamp;

    // врм
    const auto ser_msg =
        _ser.serialize(msg.get());

    const auto enc_msg = _menc.encode(ser_msg);
    sendMessage(enc_msg);
}
