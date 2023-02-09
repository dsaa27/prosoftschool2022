#ifndef DEVICEWORKSCHEDULE_H
#define DEVICEWORKSCHEDULE_H

#include <cstdint>
#include <vector>

/*!
 * \brief Параметры этапа.
 */
struct Phase
{
    std::uint64_t timeStamp{0u}; ///< Метка времени начала этапа
    std::uint8_t value{0u};      ///< Целевое значение этапа
};

/*!
 * \brief План работы устройства.
 */
struct DeviceWorkSchedule
{
    std::uint64_t deviceId{0u};    ///< Идентификатор устройства
    std::vector<Phase> schedule{}; ///< План работы устройства
};

#endif // DEVICEWORKSCHEDULE_H
