#pragma once
#include "../deviceworkschedule.h"
#include "../message.hxx"
#include <cstdint>
#include<map>
#include<memory>

class command_center {
  private:
    std::map<std::uint64_t, std::vector<Phase>> _devmap;
    std::map<std::uint64_t, std::uint64_t> _last;
    // std::map<std::uint64_t, std::pair<Phase, double>> _sd; // ско

    int64_t correction_value(const std::uint64_t device, const Phase&);
    auto find_phase(const std::uint64_t dev, const std::uint64_t stamp);
    bool has_schedule(const std::uint64_t device);

  public:
    std::unique_ptr<message> check(const std::uint64_t device, const meterage&);

    void add(const DeviceWorkSchedule&);
    void rem(const std::uint64_t device);
};
