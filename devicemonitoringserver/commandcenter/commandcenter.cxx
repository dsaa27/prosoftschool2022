#include "commandcenter.hxx"
#include "../message/message.hxx"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <memory>

void
dms::commandcenter::command_center::add(const DeviceWorkSchedule& schedule) {
    _devsch[schedule.deviceId] = schedule.schedule;
}

void
dms::commandcenter::command_center::rem(const std::uint64_t idev) {
    _devsch.erase(idev);
    _devstamp.erase(idev);
}

std::pair<bool, std::vector<Phase>::const_iterator>
dms::commandcenter::command_center::find_phase(const std::uint64_t idev,
                                               const std::uint64_t stamp) {

    const std::vector<Phase>& schedule{_devsch[idev]};

    const std::vector<Phase>::const_iterator found{
        std::find_if(schedule.cbegin(), schedule.cend(),
                     [stamp](const Phase& p) { return p.timeStamp == stamp; })};

    return make_pair(found != schedule.end(), found);
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

    bool found{false};
    std::vector<Phase>::const_iterator phase{nullptr};

    std::tie(found, phase) = find_phase(idev, meterage.timestamp());

    if (!found) {
        return std::make_unique<const dms::message::error>(
            dms::message::ERR_TYPE::NOTIMESTAMP);
    }

    const auto correction = phase->value - meterage.value();
    const auto stamp = meterage.timestamp();

    put_asd_to_hist(idev, stamp, correction);
    update_last_stamp(idev, stamp);

    return std::make_unique<const dms::message::command>(correction);
}

double
dms::commandcenter::command_center::marith(const std::uint64_t idev) {
    double sum{.0};

    for (const auto x : _devdiff[idev]) {
        sum += x.second;
    }

    return sum / _devdiff[idev].size();
}

double
dms::commandcenter::command_center::eval_asd(const std::uint64_t idev,
                                             const std::uint64_t stamp,
                                             const std::uint64_t corr) {
    _devdiff[idev][stamp] = corr;

    double ret{.0};
    const double marith{command_center::marith(idev)};

    for (const auto diff : _devdiff[idev]) {
        ret += std::pow(diff.second - marith, 2);
    }

    return std::sqrt(ret / _devdiff[idev].size());
}

void
dms::commandcenter::command_center::put_asd_to_hist(const std::uint64_t idev,
                                                    const std::uint64_t stamp,
                                                    const std::uint64_t corr) {

    _devasd[idev][stamp] = eval_asd(idev, stamp, corr);
}

double
dms::commandcenter::command_center::msqdev(std::uint64_t idev,
                                           std::uint64_t stamp) {

    return _devasd[idev][stamp];
}
