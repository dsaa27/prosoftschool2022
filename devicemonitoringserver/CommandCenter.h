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
     * \return величина корректировки для достижения этого плана или код ошибки в случае некорректных измерений
    */
    uint8_t compareMeterage(Phase& meterage, std::vector<Phase> &workSchedule) ;
private:
    struct cmp {
        bool operator() (Phase a, Phase b) const
        {
            return a.timeStamp < b.timeStamp;
        }
    };

    std::set<Phase, cmp> receivedMeterage;
    enum errorType
    {
        NoSchedule = 101,
        NoTimestamp = 102,
        Obsolete = 103
    };

    /*!
    * \brief Находит нужную фазу в плане устройства для данной метки времени
    * \param Phase - текущая фаза
     * \return фазу с значением 101, если такая не найдена в плане
    */
    static Phase getPhaseFromWorkSchedule(std::vector<Phase>& workSchedule, Phase& phase) ;
};




#endif //DEVICEMONITORINGSERVER_COMMANDCENTER_H
