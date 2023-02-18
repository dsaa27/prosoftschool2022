#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"
#include <message/message.h>
#include <message/messageserializer.h>
#include <messageencoder/messageencoder.h>

#include <string>
#include <vector>

class AbstractClientConnection;

/*!
 * \brief Класс, эмитирующий устройство.
 */
class DeviceMock
{
    NON_COPYABLE(DeviceMock)
public:
    /*!
     * \brief Конструктор.
     * \param clientConnection - владеющий указатель на объект класса клиента
     */
    DeviceMock(AbstractClientConnection* clientConnection);
    ~DeviceMock();

    /*!
     * \brief Назначить устройству идентификатор.
     * \param deviceId - идентификатор устройства
     * \return false в случае ошибки
     */
    bool bind(uint64_t deviceId);
    /*!
     * \brief Подключить устройство к серверу.
     * \param serverId - идентификатор сревера
     * \return false в случае ошибки
     */
    bool connectToServer(uint64_t serverId);
    /*!
     * \brief Установить тестовый список измерений устройства.
     * \param meterages - список измерений
     */
    void setMeterages(std::vector<Meterage> meterages);
    /*!
     * \brief Начать отправку измерений.
     */
    void startMeterageSending();

    std::vector<MessageType> getReceivedMessageTypes() const;
    std::vector<int64_t> getReceivedValues() const;

private:
    /*!
     * \brief Отправить следующее измерение.
     */
    void sendNextMeterage();
    /*!
     * \brief Обработчик установления соединения.
     */
    void onConnected();
    /*!
     * \brief Обработчик разрыва соединения.
     */
    void onDisconnected();
    /*!
     * \brief Отправить сообщение.
     */
    void sendMessage(const std::string& message) const;
    /*!
     * \brief Обработчик получения нового сообщения от сервера.
     * \param message - сообщение
     */
    void onMessageReceived(const std::string& message);

private:
    AbstractClientConnection* m_clientConnection = nullptr;
    std::vector<Meterage> m_meterages;
    uint64_t m_timeStamp = 0;

    MessageEncoder m_encoder;
    MessageSerializer m_serializer;
    std::vector<MessageType> m_messageTypes;
    std::vector<int64_t> m_receivedValues;
};

#endif // DEVICE_H
