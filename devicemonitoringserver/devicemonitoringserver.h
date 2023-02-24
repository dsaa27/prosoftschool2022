#ifndef DEVICEMONITORINGSERVER_H
#define DEVICEMONITORINGSERVER_H

#include "common.h"
#include "messageserializator.h"
#include "messageencoder.h"
#include <cstdint>
#include <string>
#include <unordered_map>

struct DeviceWorkSchedule;
class AbstractConnectionServer;
class AbstractConnection;
class CommandCenter;

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
    DeviceMonitoringServer(AbstractConnectionServer* connectionServer, std::unordered_map<uint64_t, std::vector<std::string>&>& messages);
    ~DeviceMonitoringServer();

    /*!
     * \brief Установить план работы устройств.
     */
    void setDeviceWorkSchedule(const DeviceWorkSchedule&);
    /*!
     * \brief Начать прием подключений по идентификатору \a serverId
     */
    bool listen(uint64_t serverId);
	//возвращает значение СКО для deviceId в момент вызова для последних 20 измерений
    double getMSE(uint64_t deviceId);
    //выбор метода (де)шифрования (возможно отключение при name == "")
    void setEncodingMethod(const std::string& name);
    //ввод пользовательского имени и ключа шифрования вплоть до 10 символов
    //если в строке больше 10 символов, считываются первые 10
    void registerСustomEncodingMethod(const std::string& name, const std::string& key);
    //возвращает название выбранного метода (де)шифрования
    std::string getEncodingMethodName() const;
    //начать разъединение со всеми устройствами
    void disconnect();

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

private:
    AbstractConnectionServer* m_connectionServer = nullptr;
	CommandCenter* m_commandcenter = nullptr;
    MessageSerializator* m_serializator = nullptr;
    MessageEncoder* m_encoder = nullptr;
    std::unordered_map<uint64_t, std::vector<std::string>&>& m_messagesFromClients;
};

#endif // DEVICEMONITORINGSERVER_H
