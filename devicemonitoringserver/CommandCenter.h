#ifndef DEVICEMONITORINGSERVER_COMMANDCENTER_H
#define DEVICEMONITORINGSERVER_COMMANDCENTER_H


#include <cstdint>
#include <set>
#include "deviceworkschedule.h"

class CommandCenter {
public:
    CommandCenter();
    ~CommandCenter();
    /*!
    * \brief Сравнивает полученное измерением с планом.
    * \param meterage - текущее измерение
     * \return величина корректировки для достижения этого плана
    */
    uint64_t compareMeterage(Phase meterage, DeviceWorkSchedule* workSchedule) const;
private:
    struct cmp {
        bool operator() (Phase a, Phase b) const
        {
            return a.timeStamp < b.timeStamp;
        }
    };

    std::set<Phase, cmp> receivedMeterage = {};
    enum errorType
    {
        NoSchedule = 101,
        NoTimestamp = 102,
        Obsolete = 103
    };

    /*!
    * \brief Находит нужную фазу в плане устройства для данной метки времени
    * \param Phase - текущая фаза
     * \return nullptr, если такая не найдена в плане
    */
    Phase* getPhaseFromWorkSchedule(DeviceWorkSchedule* workSchedule, Phase phase) const
    {
        for (Phase ph : workSchedule->schedule)
        {
            if (ph.timeStamp == phase.timeStamp)
                return &ph;
        }
        return nullptr;
    };
};




#endif //DEVICEMONITORINGSERVER_COMMANDCENTER_H
