#ifndef DEVICEMONITORINGSERVER_COMMANDCENTER_H
#define DEVICEMONITORINGSERVER_COMMANDCENTER_H


#include <cstdint>
#include <set>
#include <map>
#include "deviceworkschedule.h"

class CommandCenter {
public:
    enum errorType
    {
        NoSchedule = 101,
        NoTimestamp = 102,
        Obsolete = 103
    };

    CommandCenter();
    ~CommandCenter();
    /*!
    * \brief Сравнивает полученное измерением с планом.
    * \param phase - текущая фаза
     * \return величина корректировки для достижения этого плана или код ошибки в случае некорректных измерений
    */
    uint8_t checkMeterageInPhase(Phase& phase, std::vector<Phase> &workSchedule) ;
private:
    std::map<Phase, double> standardDeviationForPhase;
    std::vector<uint8_t> differenceNeedAndActualValue;
    void countStandardDeviationForPhase(Phase phase);
    struct cmp {
        bool operator() (Phase a, Phase b) const
        {
            return a.timeStamp < b.timeStamp;
        }
    };

    std::set<Phase, cmp> receivedMeterage;

    /*!
    * \brief Находит нужную фазу в плане устройства для данной метки времени
    * \param Phase - текущая фаза
     * \return фазу с значением 101, если такая не найдена в плане
    */
    static Phase getPhaseFromWorkSchedule(std::vector<Phase>& workSchedule, Phase& phase) ;
};




#endif //DEVICEMONITORINGSERVER_COMMANDCENTER_H
