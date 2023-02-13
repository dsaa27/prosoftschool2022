#ifndef DEVICEMONITORINGSERVER_MESSAGEENCODER_H
#define DEVICEMONITORINGSERVER_MESSAGEENCODER_H

#include <string>
#include <map>
#include "BaseEncoderExecutor.h"
#include <optional>
#include <vector>
#include "ROT3.h"
#include "Mirror.h"
#include "Multiply41.h"

/*!
 * Класс для шифрования и дешифрования сериализованных сообщений
 * для последующей передачи через клиент-серверное соединение.
 */
class MessageEncoder
        {
public:
    MessageEncoder()=default;
    ~MessageEncoder();
    std::vector<std::string> getAvailableAlgorithms();
    /*!
    * \brief Зашифровать сообщение
    * \param message - сообщение
    * \return зашифрованное сообщение или nullopt, если не удалось зашифровать
   */
    std::optional<std::string> encode(const std::string& message);
    /*!
    * \brief Дешифровать сообщение
    * \param message - сообщение
    * \return дешифрованное сообщение или nullopt, если не удалось дешифровать
   */
    std::optional<std::string> decode(const std::string& message);
    /*!
    * \brief выбрать алгоритм шифрования
    *  \param algorithm - имя алгоритма
    * \return наличие в числе зарегистрированных алгоритмов
   */
    bool chooseAlgorithm(const std::string& algorithm);
    /*!
    * \brief добавить алгоритм шифрования
    * \param algorithm - владеющий указатель на алгоритм
    * \return false - если не удалось
   */
    bool addAlgorithm(BaseEncoderExecutor* algorithm);
private:
    BaseEncoderExecutor* m_currentAlgorithm = nullptr;
    std::map<std::string, BaseEncoderExecutor*> m_allAlgorithms = {{"ROT3", new ROT3()} , {"Mirror", new Mirror()},
                                                                   {"Multiply41", new Multiply41()}};
};


#endif //DEVICEMONITORINGSERVER_MESSAGEENCODER_H
