#include "commandcenter.hxx"
#include "../message.hxx"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>

void
command_center::add(const DeviceWorkSchedule& schedule) {
    _devsch[schedule.deviceId] = schedule.schedule;
}

void
command_center::rem(const std::uint64_t idev) {
    _devsch.erase(idev);
    _devstamp.erase(idev);
}

auto
command_center::find_phase(const std::uint64_t idev,
                           const std::uint64_t stamp) {

    const std::vector<Phase>& schedule{_devsch[idev]};

    return std::find_if(
        schedule.cbegin(), schedule.cend(),
        [stamp](const Phase p) { return p.timeStamp == stamp; });
}

bool
command_center::has_schedule(const std::uint64_t idev) {
    return _devsch.find(idev) != _devsch.end();
}

void
command_center::update_last_stamp(const std::uint64_t idev,
                                  const std::uint64_t stamp) {
    _devstamp[idev] = stamp;
}

std::unique_ptr<const message>
command_center::check(const std::uint64_t idev, const meterage& meterage) {
    const auto last = _devstamp.find(idev);

    if (last != _devstamp.end()) {
        if (meterage.timestamp() < last->second) {
            return std::make_unique<error>(ERR_TYPE::OBSOLETE);
        }
    }

    if (!has_schedule(idev)) {
        return std::make_unique<error>(ERR_TYPE::NOSCHEDULE);
    }

    const auto phase = find_phase(idev, meterage.timestamp());

    if (phase == std::end(_devsch[idev])) {
        return std::make_unique<error>(ERR_TYPE::NOTIMESTAMP);
    }

    update_last_stamp(idev, meterage.timestamp());
    return std::make_unique<command>(phase->value - meterage.value());
}
