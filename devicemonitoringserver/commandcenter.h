#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <devicemock.h>
#include <MessageSerializer.h>
#include <deviceworkschedule.h>

#include <map>


struct Device{

    //uint64_t deviceId = 0;

    DeviceWorkSchedule Schedule;

    uint64_t expectedTimestamp = 0;

    //uint64_t - метка времени на котором было получено СКО
    //double - значение СКО
    std::map <uint64_t, double> m_MSE;

    double last_MSE;
};


class CommandCenter
{
public:
    //CommandCenter();
    /*!
     * \brief Реализация алгоритма регистрации нового устройства в памяти комадного центра
     * \param deviceId - ID нового устройста
     */
    void RegisterDevice (uint64_t& deviceId);

    /*!
     * \brief Реализация алгоритма выдачи решения от командного центра
     * \param Message_fromServer - сообщение, которое приходит от сервера
     * \param Message_toServer - сообщение, которое выдаёт командный центр (ошибка или команда)
     */
    void GetMessage (uint64_t& deviceId, std::string& Message_fromServer, std::string& Message_toServer);

    /*!
     * \brief Реализация алгоритма задания плана работы устройства
     * \param deviceId - ID устройста для которого задаётся план работы
     * \param Schedule - план работу устройства, который необходимо задать для устройства
     */
    void SetSchedule (uint64_t& deviceId, DeviceWorkSchedule& Schedule);

private:
    //uint64_t - ключ, ID устройства
    //Device - значения устройства
    std::map <uint64_t, Device> m_Device_Map;

    MessageSerialiser* m_serialize;

    //std::vector <Device> m_Device_Vector;
};



#endif // COMMANDCENTER_H
