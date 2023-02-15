#pragma once
#include "../deviceworkschedule.h"
#include "../message/message.hxx"
#include <cstdint>
#include <map>
#include <memory>
#include <set>

namespace dms {
namespace commandcenter {
class command_center;
}
} // namespace dms

class dms::commandcenter::command_center {
  private:
    std::map<std::uint64_t /* idev */, std::vector<Phase> /* schedule */>
        _devsch{};

    std::map<std::uint64_t, /* idev */ std::uint64_t /* last meterage stamp */>
        _devstamp{};

    std::map<std::uint64_t /* idev */,
             std::map<uint64_t /* tstamp */, double /* СКО ОУ */>>
        _devasd{};

    // история корректировок
    std::map<std::uint64_t, std::map<std::uint64_t, std::int8_t>> _devdiff{};

    std::pair<bool /* found */, std::vector<Phase>::const_iterator>
    find_phase(const std::uint64_t idev, const std::uint64_t tstamp);

    bool
    has_schedule(const std::uint64_t idev);

    void
    update_last_stamp(const std::uint64_t idev, const std::uint64_t stamp);

    void
    put_diff_to_hist(const std::uint64_t idev, const std::uint64_t,
                     const std::int8_t);

    void
    put_asd_to_hist(const std::uint64_t idev, const std::uint64_t stamp,
                    const uint64_t);

    double
    eval_asd(const uint64_t idev, const uint64_t, const uint64_t);

  public:
    double
    marith(const std::uint64_t idev);

  public:
    // Проверка измерения устройства с плановым значением
    std::unique_ptr<const dms::message::message>
    check(const std::uint64_t idev, const dms::message::meterage&);

    // Добавить устройство
    void
    add(const DeviceWorkSchedule&);

    // Удалить устройство
    void
    rem(const std::uint64_t idev);

    // Узнать СКО ошибки управления
    // для указанного устройства в указанное время
    // (m)ean (sq)uare (dev)iation
    double
    msqdev(std::uint64_t idev, std::uint64_t stamp);
};
