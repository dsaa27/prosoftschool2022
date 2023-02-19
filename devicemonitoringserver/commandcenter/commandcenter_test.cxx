#include "../deviceworkschedule.h"
#include "../message/message.hxx"
#include "commandcenter.hxx"
#include <cassert>
#include <iostream>
using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "No Schedule" << endl;
        const std::uint64_t idev{1000u};

        dms::commandcenter::command_center cc{};
        const auto response = cc.check(idev, {1u, 10u});

        assert(dms::message::MSG_TYPE::ERROR == response->type());
        assert(dms::message::ERR_TYPE::NOSCHEDULE ==
               dynamic_cast<const dms::message::error*>(response.get())->err());
    }

    {
        cout << "Command" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{
            .deviceId = idev, .schedule{{0u, 43u}, {1u, 23u}, {2u, 10u}}};

        dms::commandcenter::command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, {0u, 17u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(43 - 17 ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());
        }

        {
            const auto response = cc.check(idev, {1u, 41u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(23 - 41 ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());
        }

        {
            const auto response = cc.check(idev, {2u, 10u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(0u ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());
        }
    }

    {
        cout << "No Timestamp" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{.deviceId = idev,
                                          .schedule{{0, 43}, {1, 23}}};

        dms::commandcenter::command_center cc{};
        cc.add(schedule);

        const auto response = cc.check(idev, {2, 10});

        assert(dms::message::MSG_TYPE::ERROR == response->type());
        assert(dms::message::ERR_TYPE::NOTIMESTAMP ==
               dynamic_cast<const dms::message::error*>(response.get())->err());
    }

    {
        cout << "Obsolete" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{.deviceId = idev,
                                          .schedule{{0u, 43u}, {1u, 23u}}};

        dms::commandcenter::command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, {1u, 81u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(23 - 81 ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());
        }

        {
            const auto response = cc.check(idev, {0u, 43});

            assert(dms::message::MSG_TYPE::ERROR == response->type());
            assert(dms::message::ERR_TYPE::OBSOLETE ==
                   dynamic_cast<const dms::message::error*>(response.get())
                       ->err());
        }
    }

    {
        cout << "Device Remove" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{.deviceId = idev,
                                          .schedule{{{0u, 43u}, {1u, 23u}}}};

        dms::commandcenter::command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, {1u, 43u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(23 - 43 ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());
        }

        {
            const auto response = cc.check(idev, {0u, 43u});

            assert(dms::message::MSG_TYPE::ERROR == response->type());
            assert(dms::message::ERR_TYPE::OBSOLETE ==
                   dynamic_cast<const dms::message::error*>(response.get())
                       ->err());
        }

        cc.rem(idev);

        {
            const auto response = cc.check(idev, {1u, 23u});

            assert(dms::message::MSG_TYPE::ERROR == response->type());
            assert(dms::message::ERR_TYPE::NOSCHEDULE ==
                   dynamic_cast<const dms::message::error*>(response.get())
                       ->err());
        }
    }

    {
        cout << "Mean Square Deviation" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{
            .deviceId = idev,
            .schedule{{{0u, 43u}, {1u, 23u}, {2, 10}, {3, 15}}}};

        const double prec{1e-5};

        dms::commandcenter::command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, {0u, 20u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(43 - 20 ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());

            // avg: 23
            // sum: (23 - 23)^2
            // sqrt(0 / 1) = 0

            assert(std::abs(0.0 - cc.msqdev(idev, 0u)) < prec);
        }

        {
            const auto response = cc.check(idev, {1u, 20u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(23 - 20 ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());

            // avg: (23 + 3) / 2 = 13
            // sum: (23 - 13)^2 + (3 - 13)^2 = 200
            // sqrt(200 / 2) = 10

            assert(std::abs(10.0 - cc.msqdev(idev, 1u)) < prec);
        }

        {
            const auto response = cc.check(idev, {2u, 8u});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(10u - 8u ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());

            // avg: (23 + 3 + 2) / 3 = 9.33333
            // sum: (23 - 9.33333)^2 + (3 - 9.33333)^2 + (2 - 9.33333)^2 =
            // sqrt(280.6666667 / 3) ≈ 9.672412086

            assert(std::abs(9.672412 - cc.msqdev(idev, 2u)) < prec);
        }

        {
            const auto response = cc.check(idev, {1u, 20u});

            assert(dms::message::MSG_TYPE::ERROR == response->type());
            assert(dms::message::ERR_TYPE::OBSOLETE ==
                   dynamic_cast<const dms::message::error*>(response.get())
                       ->err());
        }

        {
            const auto response = cc.check(idev, {3, 15});

            assert(dms::message::MSG_TYPE::COMMAND == response->type());
            assert(0 ==
                   dynamic_cast<const dms::message::command*>(response.get())
                       ->value());

            // avg: (23 + 3 + 2 + 0) / 4 = 7
            // sum: (23 - 7)^2 + (3 - 7)^2 + (2 - 7)^2 + (0 - 7)^2 = 346
            // sqrt(346 / 4) = 9.300537

            assert(std::abs(9.300537 - cc.msqdev(idev, 3u)) < prec);
        }

        {
            const auto response = cc.check(idev, {4u, 8u});

            assert(dms::message::MSG_TYPE::ERROR == response->type());
            assert(dms::message::ERR_TYPE::NOTIMESTAMP ==
                   dynamic_cast<const dms::message::error*>(response.get())
                       ->err());
        }
    }
}
