#pragma once
#include "../deviceworkschedule.h"
#include "../message.hxx"
#include <cstdint>
#include <map>
#include <memory>

class command_center {
  private:
    // (idev, schedule)
    std::map<std::uint64_t, std::vector<Phase>> _devsch{};

    // (idev, last meterage stamp)
    std::map<std::uint64_t, std::uint64_t> _devstamp{};

    // std::map<std::uint64_t, std::pair<Phase, double>> _sd{}; // ско

    std::int8_t
    correction_value(const std::uint64_t idev, const Phase&);

    auto
    find_phase(const std::uint64_t idev, const std::uint64_t tstamp);

    bool
    has_schedule(const std::uint64_t idev);

    void
    update_last_stamp(const std::uint64_t idev, const std::uint64_t stamp);

  public:
    std::unique_ptr<const message>
    check(const std::uint64_t idev, const meterage&);

    void
    add(const DeviceWorkSchedule&);

    void
    rem(const std::uint64_t idev);
};
