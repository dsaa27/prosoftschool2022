#ifndef DEVICEMONITORINGSERVER_SINGLETONENCODER_H
#define DEVICEMONITORINGSERVER_SINGLETONENCODER_H

#include <map>
#include <cstdint>
#include "MessageEncoder.h"
/*!
 * Добавила этот класс чтобы иметь какую-то синхронизацию шифрования между сервером и устройством
 *  т.е при регистрации новых алгоритмов или смене текущего алгоритма, оба получали изменения.
 * \brief Класс, отвечающий за договоренность шифрования между сервером и клиентоми
 */
class SingletonEncoder {
    private:
        /*!
        * \brief Назначить устройству шифровальщик
        * \param deviceId - идентификатор устройства
        */
        void addDeviceEncoder(uint64_t deviceId);
       /*!
       * \brief список устройств и их шифровальщиков
       */
        std::map<uint64_t, MessageEncoder*> devicesEncoder;
        static SingletonEncoder * p_instance;
        SingletonEncoder()=default;
    public:
        /*!
        * \brief получить шифровальщик устройства
        * \param deviceId - идентификатор устройства
        */
        MessageEncoder* getDeviceEncoder(uint64_t deviceId);

        static SingletonEncoder* getInstance() {
            if(!p_instance)
                p_instance = new SingletonEncoder();
            return p_instance;
        }
    };

#endif //DEVICEMONITORINGSERVER_SINGLETONENCODER_H
