#include "commandcenter.hxx"
#include "../message.hxx"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <utility>
#include<iostream>

void command_center::add(const DeviceWorkSchedule& schedule) {
    _devmap[schedule.deviceId] = schedule.schedule;
}

void command_center::rem(const std::uint64_t device) {
    _devmap.erase(device);
}

auto command_center::find_phase(const std::uint64_t idev,
                                const std::uint64_t stamp) {

    const std::vector<Phase>& schedule{_devmap[idev]};

    return std::find_if(schedule.begin(), schedule.end(),
                        [stamp](const Phase p) {
                        return p.timeStamp == stamp; });
}

bool command_center::has_schedule(const std::uint64_t device) {
    return _devmap.find(device) != _devmap.end();
}

std::unique_ptr<message> command_center::check(const std::uint64_t device,
                                               const meterage& meterage) {
    const auto last = _last.find(device);

    if (last != _last.end()) {
        if (meterage.timestamp() < last->second) {
            return std::make_unique<error>(ERR_TYPE::OBSOLETE);
        }
    }

    if (!has_schedule(device)) {
        return std::make_unique<error>(ERR_TYPE::NOSCHEDULE);
    }

    const auto phase = find_phase(device, meterage.timestamp());

    if (phase == std::end(_devmap[device])) {
        return std::make_unique<error>(ERR_TYPE::NOTIMESTAMP);
    }

    _last[device] = meterage.timestamp();
    return std::make_unique<command>(phase->value - meterage.value());
}
