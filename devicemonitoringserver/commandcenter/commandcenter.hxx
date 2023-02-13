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
    // (idev, schedule)
    std::map<std::uint64_t, std::vector<Phase>> _devsch{};

    // (idev, last meterage stamp)
    std::map<std::uint64_t, std::uint64_t> _devstamp{};

    // (idev, {(метка времени, asd)})
    std::map<std::uint64_t, std::map<uint64_t, double>> _devasd{};

    // история корректировок
    std::map<std::uint64_t, std::map<std::uint64_t, std::int8_t>> _devdiff{};

    auto
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

    // ско
    double
    _asd(const uint64_t idev, const uint64_t, const uint64_t);

  public:
    // ср.арифм.
    double
    avg(const std::uint64_t idev);

  public:
    std::unique_ptr<const dms::message::message>
    check(const std::uint64_t idev, const dms::message::meterage&);

    void
    add(const DeviceWorkSchedule&);

    void
    rem(const std::uint64_t idev);

    double
    asd(std::uint64_t idev, std::uint64_t stamp);
};
