#include "commandcenter.hxx"
#include "../message.hxx"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>

void
command_center::add(const DeviceWorkSchedule& schedule) {
    _devmap[schedule.deviceId] = schedule.schedule;
}

void
command_center::rem(const std::uint64_t idev) {
    _devmap.erase(idev);
    _last.erase(idev);
}

auto
command_center::find_phase(const std::uint64_t idev,
                           const std::uint64_t stamp) {

    const std::vector<Phase>& schedule{_devmap[idev]};

    return std::find_if(
        schedule.begin(), schedule.end(),
        [stamp](const Phase p) { return p.timeStamp == stamp; });
}

bool
command_center::has_schedule(const std::uint64_t idev) {
    return _devmap.find(idev) != _devmap.end();
}

std::unique_ptr<message>
command_center::check(const std::uint64_t idev, const meterage& meterage) {
    const auto last = _last.find(idev);

    if (last != _last.end()) {
        if (meterage.timestamp() < last->second) {
            return std::make_unique<error>(ERR_TYPE::OBSOLETE);
        }
    }

    if (!has_schedule(idev)) {
        return std::make_unique<error>(ERR_TYPE::NOSCHEDULE);
    }

    const auto phase = find_phase(idev, meterage.timestamp());

    if (phase == std::end(_devmap[idev])) {
        return std::make_unique<error>(ERR_TYPE::NOTIMESTAMP);
    }

    _last[idev] = meterage.timestamp();
    return std::make_unique<command>(phase->value - meterage.value());
}
