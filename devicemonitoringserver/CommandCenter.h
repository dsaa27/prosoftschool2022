#ifndef DEVICEMONITORINGSERVER_COMMANDCENTER_H
#define DEVICEMONITORINGSERVER_COMMANDCENTER_H


#include <cstdint>
#include <set>
#include <map>
#include "deviceworkschedule.h"

/*!
   * Класс командного центра - отвечает за сверение пришедших измерений с планом и подсчитыает СКО ошибки выполнения плана.
   */
class CommandCenter {
public:
    enum errorType
    {
        NoSchedule = 101,
        NoTimestamp = 102,
        Obsolete = 103
    };

    CommandCenter()=default;
    ~CommandCenter()=default;
    /*!
    * \brief Сравнивает полученное измерением с планом.
    * \param phase - текущая фаза
     * \return величина корректировки для достижения этого плана или код ошибки в случае некорректных измерений
    */
    int64_t checkMeterageInPhase(Phase phase, uint64_t deviceId);

    /*!
    * \brief возвращает СКО ошибки выполения плана для последней отправленной фазы
     * \return ско ошибки
    */
    double getStandardDeviation(uint64_t deviceId);

    /*!
    * \brief добавляет устройство и его план
    */
    void addDevice(const DeviceWorkSchedule& workSchedule);

    /*!
    * \brief удаляет устройство из списков
    */
    void deleteDevice(uint64_t deviceId);
private:
    /*!
  * \brief считает ско ошибки для текущей фазы
     * \return ско ошибки
  */
    double countStandardDeviationForPhase(Phase phase, uint64_t deviceId);
    struct cmp {
        bool operator() (Phase a, Phase b) const
        {
            return a.timeStamp < b.timeStamp;
        }
    };

    std::map<uint64_t, std::vector<Phase>> devicesWorkSchedule;
    std::map<uint64_t, std::vector<double>> devicesStandDeviation;
    std::map<uint64_t, std::vector<int64_t>> devicesDifferenceNeededAndActualValue;
    std::set<Phase, cmp> receivedMeterage;

    /*!
    * \brief Находит нужную фазу в плане устройства для данной метки времени
    * \param Phase - текущая фаза
     * \return фазу с значением 101, если такая не найдена в плане
    */
    static Phase getPhaseFromWorkSchedule(std::vector<Phase>& workSchedule, Phase& phase) ;
};




#endif //DEVICEMONITORINGSERVER_COMMANDCENTER_H
