#ifndef DEVICEMONITORINGSERVER_H
#define DEVICEMONITORINGSERVER_H

#include "common.h"
#include <message/messageserializer.h>
#include <messageencoder/messageencoder.h>
#include <commandcenter/commandcenter.h>

#include <cstdint>
#include <string>
#include <map>

struct DeviceWorkSchedule;
class AbstractConnectionServer;
class AbstractConnection;

/*!
 * \brief Класс сервера для мониторинга состояния устройств.
 */
class DeviceMonitoringServer
{
    NON_COPYABLE(DeviceMonitoringServer)
public:
    /*!
     * \brief Конструктор.
     * \param connectionServer - владеющий указатель на сервер для приема подключений
     */
    DeviceMonitoringServer(AbstractConnectionServer* connectionServer);
    ~DeviceMonitoringServer();

    /*!
     * \brief Установить план работы устройств.
     */
    void setDeviceWorkSchedule(const DeviceWorkSchedule&);
    /*!
     * \brief Начать прием подключений по идентификатору \a serverId
     */
    bool listen(uint64_t serverId);

    std::vector<PhaseStatistics> getDeviceStatistics(uint64_t deviceId) const;

private:
    /*!
     * \brief Отправить сообщение устройству.
     * \param deviceId - идентификатор устройства
     * \param message - сообщение
     */
    void sendMessage(uint64_t deviceId, const std::string& message);
    /*!
     * \brief Обработчик приема нового сообщения от устройства.
     * \param deviceId - идентификатор устройства
     * \param message - сообщение
     */
    void onMessageReceived(uint64_t deviceId, const std::string& message);
    /*!
     * \brief Обработчик поступления нового входящего подключения.
     * \param conn - невладеющий указатель на объект подключения
     */
    void onNewIncomingConnection(AbstractConnection* conn);
    /*!
     * \brief Обработчик разрыва соединения.
     * \param deviceId - идентификатор устройства
     */
    void onDisconnected(uint64_t clientId);

private:
    void addMessageHandler(AbstractConnection* conn);
    void addDisconnectedHandler(AbstractConnection* conn);
    bool convertToMessageDto(const std::string& encodedMessage, MessageDto& messageDto) const;
    bool convertToEncodedMessage(const MessageDto& messageDto, std::string& encodedMessage) const;


private:
    AbstractConnectionServer* m_connectionServer = nullptr;

    CommandCenter m_commandCenter;
    MessageEncoder m_encoder;
    MessageSerializer m_serializer;
    std::map<uint64_t, bool> m_connectedDevices;
};

#endif // DEVICEMONITORINGSERVER_H
