#include "commandcenter.hxx"
#include "../message/message.hxx"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>

void
dms::commandcenter::command_center::add(const DeviceWorkSchedule& schedule) {
    _devsch[schedule.deviceId] = schedule.schedule;
}

void
dms::commandcenter::command_center::rem(const std::uint64_t idev) {
    _devsch.erase(idev);
    _devstamp.erase(idev);
}

auto
dms::commandcenter::command_center::find_phase(const std::uint64_t idev,
                                               const std::uint64_t stamp) {

    const std::vector<Phase>& schedule{_devsch[idev]};

    return std::find_if(
        schedule.cbegin(), schedule.cend(),
        [stamp](const Phase p) { return p.timeStamp == stamp; });
}

bool
dms::commandcenter::command_center::has_schedule(const std::uint64_t idev) {
    return _devsch.find(idev) != _devsch.end();
}

void
dms::commandcenter::command_center::update_last_stamp(
    const std::uint64_t idev, const std::uint64_t stamp) {
    _devstamp[idev] = stamp;
}

std::unique_ptr<const dms::message::message>
dms::commandcenter::command_center::check(
    const std::uint64_t idev, const dms::message::meterage& meterage) {

    const auto last = _devstamp.find(idev);

    if (last != _devstamp.end()) {
        if (meterage.timestamp() < last->second) {
            return std::make_unique<const dms::message::error>(
                dms::message::ERR_TYPE::OBSOLETE);
        }
    }

    if (!has_schedule(idev)) {
        return std::make_unique<const dms::message::error>(
            dms::message::ERR_TYPE::NOSCHEDULE);
    }

    const auto phase = find_phase(idev, meterage.timestamp());

    if (phase == std::end(_devsch[idev])) {
        return std::make_unique<dms::message::error>(
            dms::message::ERR_TYPE::NOTIMESTAMP);
    }

    const auto correction = phase->value - meterage.value();
    const auto stamp = meterage.timestamp();

    put_asd_to_hist(idev, stamp, correction);
    update_last_stamp(idev, stamp);

    return std::make_unique<const dms::message::command>(correction);
}

// средняя ошибка управления
double
dms::commandcenter::command_center::avg(const std::uint64_t idev) {
    double sum{.0};

    for (const auto x : _devdiff[idev]) {
        sum += x.second;
    }

    return sum / _devdiff[idev].size();
}

// среднее квадратичное ошибки управления
double
dms::commandcenter::command_center::_asd(const std::uint64_t idev,
                                         const std::uint64_t stamp,
                                         const std::uint64_t corr) {
    _devdiff[idev][stamp] = corr;

    double ret{.0};
    const double avg{command_center::avg(idev)};

    for (const auto x : _devdiff[idev]) {
        ret += std::pow(x.second - avg, 2);
    }

    return std::sqrt(ret / _devdiff[idev].size());
}

void
dms::commandcenter::command_center::put_asd_to_hist(const std::uint64_t idev,
                                                    const std::uint64_t stamp,
                                                    const std::uint64_t corr) {

    if (_devasd.find(idev) == _devasd.end()) {
        _devasd[idev] = {};
    }

    _devasd[idev][stamp] = _asd(idev, stamp, corr);
}

double
dms::commandcenter::command_center::asd(std::uint64_t idev,
                                        std::uint64_t stamp) {
    return _devasd[idev][stamp];
}
