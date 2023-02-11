#ifndef DEVICEMONITORINGSERVER_COMMANDCENTER_H
#define DEVICEMONITORINGSERVER_COMMANDCENTER_H


#include <cstdint>
#include <set>
#include <map>
#include <optional>
#include "deviceworkschedule.h"

/*!
   * Класс командного центра - отвечает за сверку пришедших измерений с планом и подсчитывает СКО ошибки выполнения плана.
   */
class CommandCenter {
public:

    /*!
    * \brief Типы ошибок
    */
    enum errorType
    {
        NoError = 0, // ошибок нет
        NoSchedule = 101, // У устройства отсутствует план
        NoTimestamp, // Текущая метка времени отсутствует в плане
        Obsolete // Поступило измерение с устаревшей меткой времени
    };

    /*!
    * \brief результат проверки текущего измерения
    */
    struct CheckResult final {
        int64_t valueToCorrect; //значение на которое нужно скорректировать параметр
        errorType errorCode = NoError;// код ошибки
    };

    /*!
    * \brief Сравнивает полученное измерение с планом.
    * \param phase - текущая фаза
     * \return величина корректировки для достижения этого плана или код ошибки в случае некорректных измерений
    */
    CheckResult checkMeterageInPhase(Phase& phase, uint64_t deviceId);

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
    std::map<uint64_t, std::vector<Phase>> m_devicesWorkSchedule;
    std::map<uint64_t, std::vector<double>> m_devicesStandDeviation;
    std::map<uint64_t, std::vector<int64_t>> m_devicesDifferenceNeededAndActualValue;

    struct cmp {
        bool operator() (Phase a, Phase b) const
        {
            return a.timeStamp < b.timeStamp;
        }
    };
    std::set<Phase, cmp> m_receivedMeterage;

    /*!
    * \brief считает ско ошибки для текущей фазы
    * \return ско ошибки
    */
    double countStandardDeviationForPhase(uint64_t deviceId);

    /*!
    * \brief считает ско ошибки для текущей фазы
    * \return ско ошибки
    */
    double roundTo2(double value);

    /*!
    * \brief Находит нужную фазу в плане устройства для данной метки времени
    * \param phase - текущая фаза
    * \param deviceId - идентификатор устройства
    * \return nullopt, если такая не найдена в плане
    */
    std::optional<Phase> getPhaseFromWorkSchedule(uint64_t deviceId, Phase& phase);

};




#endif //DEVICEMONITORINGSERVER_COMMANDCENTER_H
