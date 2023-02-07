#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#include "messagecommon.h"
#include <map>
#include <cmath>

struct DeviceInfo
{
    uint64_t m_lastTimestamp = 0;
    float m_mse = 0;
    uint64_t m_countCommand = 0;
};

class CommandCenter
{
public:
    /*!
     * \brief Установить план работы устройства.
     */
    void setSchedule(const DeviceWorkSchedule& deviceWorkSchedule);
    /*!
     * \brief Выработать команду устройству.
     * \param deviceId - идентификатор устройства.
     * \param message - сообщение от устройтсва.
     */
    MessageStruct generateCommand(uint64_t deviceId, MessageStruct message);
    /*!
     * \brief Получить СКО ошибки управления устройством.
     */
    float getMse(uint64_t deviceId);
private:
    void updateMse(uint64_t deviceId, int dx);
private:
    std::map<uint64_t, std::vector<Phase>> m_scheduleMap;
    std::map <uint64_t, DeviceInfo> deviceInfoMap;
};

#endif // COMMANDCENTER_H
