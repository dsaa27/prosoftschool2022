#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"
#include "encoding/MessageEncoder.h"
#include "serialization/MessageSerializator.h"


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
     * \param serverId - идентификатор сервера
     * \return false в случае ошибки
     */
    bool connectToServer(uint64_t serverId);
    /*!
     * \brief Установить тестовый список измерений устройства.
     * \param measurements - список измерений
     */
    void setMeterages(std::vector<uint8_t> meterages);
    /*!
     * \brief Начать отправку измерений.
     */
    void startMeterageSending();
    /*!
     * \brief Выбор алгоритма кодирования сообщений
     * \param name - название алгоритма
     * \return результат попытки назначить алгоритм
     */
    bool chooseEncodingAlgorithm(const std::string& name);
    /*!
     * \brief Регистрация нового алгоритма шифрования
     * \param algorithm - объект класса, унаследованный от BaseEncoderExecutor
     * \return результат попытки добавления алгоритма
     */
    bool registerEncodingAlgorithm(BaseEncoderExecutor* algorithm);
    /*!
     * \brief Получить список сообщений от сервера
     * \return вектор, содержащий ответы от сервера
     */
    std::vector<std::string> getResponses();

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
    MessageEncoder m_encoder;
    MessageSerializator m_serializator;
    std::vector<std::string> m_responses;
    std::vector<uint64_t> m_receivedCommands;
    AbstractClientConnection* m_clientConnection = nullptr;
    std::vector<uint8_t> m_meterages;
    uint64_t m_timeStamp = 0;
};

#endif // DEVICE_H
