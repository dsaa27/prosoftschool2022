#include "../deviceworkschedule.h"
#include "../message.hxx"
#include "commandcenter.hxx"
#include <cassert>
#include <iostream>
using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Test #1" << endl;
        const std::uint64_t idev{1000u};

        command_center cc{};
        const auto response = cc.check(idev, meterage{1u, 10u});

        assert(MSG_TYPE::ERROR == response->type());
        assert(ERR_TYPE::NOSCHEDULE ==
               dynamic_cast<const error*>(response.get())->err());
    }

    {
        cout << "Test #2" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{
            .deviceId = idev, .schedule = {{0u, 43u}, {1u, 23u}, {2u, 10u}}};

        command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, meterage(0u, 17u));

            assert(MSG_TYPE::COMMAND == response->type());
            assert(43u - 17u ==
                   dynamic_cast<const command*>(response.get())->value());
        }

        {
            const auto response = cc.check(idev, meterage(1u, 41u));

            assert(MSG_TYPE::COMMAND == response->type());
            assert(23u - 41u ==
                   dynamic_cast<const command*>(response.get())->value());
        }

        {
            const auto response = cc.check(idev, meterage(2u, 10u));

            assert(MSG_TYPE::COMMAND == response->type());
            assert(0u == dynamic_cast<const command*>(response.get())->value());
        }
    }

    {
        cout << "Test #3" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{.deviceId = idev,
                                          .schedule = {{0, 43}, {1, 23}}};

        command_center cc{};
        cc.add(schedule);

        const auto response = cc.check(idev, {2, 10});

        assert(MSG_TYPE::ERROR == response->type());
        assert(ERR_TYPE::NOTIMESTAMP ==
               dynamic_cast<const error*>(response.get())->err());
    }

    {
        cout << "Test #4" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{.deviceId = idev,
                                          .schedule = {{0u, 43u}, {1u, 23u}}};

        command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, {1u, 81u});

            assert(MSG_TYPE::COMMAND == response->type());
            assert(23 - 81 ==
                   dynamic_cast<const command*>(response.get())->value());
        }

        {
            const auto response = cc.check(idev, {0, 43});

            assert(MSG_TYPE::ERROR == response->type());
            assert(ERR_TYPE::OBSOLETE ==
                   dynamic_cast<const error*>(response.get())->err());
        }
    }

    {
        cout << "Test #5" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{.deviceId = idev,
                                          .schedule{{{0u, 43u}, {1u, 23u}}}};

        command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, meterage{1, 43u});
            assert(MSG_TYPE::COMMAND == response->type());
            assert(23u - 43u ==
                   dynamic_cast<const command*>(response.get())->value());
        }

        {
            const auto response = cc.check(idev, meterage{0u, 43u});
            assert(MSG_TYPE::ERROR == response->type());
            assert(ERR_TYPE::OBSOLETE ==
                   dynamic_cast<const error*>(response.get())->err());
        }

        cc.rem(idev);

        {
            const auto response = cc.check(idev, meterage{1u, 23u});

            assert(MSG_TYPE::ERROR == response->type());
            assert(ERR_TYPE::NOSCHEDULE ==
                   dynamic_cast<const error*>(response.get())->err());
        }
    }

    {
        cout << "Test #6" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{
            .deviceId = idev,
            .schedule{{{0u, 43u}, {1u, 23u}, {2, 10}, {3, 15}}}};

        const double prec{1e-5};

        command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, {0, 20});

            assert(MSG_TYPE::COMMAND == response->type());
            assert(43 - 20 ==
                   dynamic_cast<const command*>(response.get())->value());

            // avg: 23
            // sum: (23 - 23)^2

            assert(std::abs(0.0 - cc.asd(idev, 0)) < prec);
        }

        {
            const auto response = cc.check(idev, {1, 20});

            assert(MSG_TYPE::COMMAND == response->type());
            assert(23 - 20 ==
                   dynamic_cast<const command*>(response.get())->value());

            // avg: (23 + 3) / 2 = 13
            // sum: (23 - 13)^2 + (3 - 13)^2 = 200

            assert(std::abs(10.0 - cc.asd(idev, 1)) < prec);
        }

        {
            const auto response = cc.check(idev, {2, 8});

            assert(MSG_TYPE::COMMAND == response->type());
            assert(10 - 8 ==
                   dynamic_cast<const command*>(response.get())->value());

            // avg: (23 + 3 + 2) / 3 = 9.33333
            // sum: (23 - 9.33333)^2 + (3 - 9.33333)^2 + (2 - 9.33333)^2 =
            // sqrt(280.6666667 / 3) ≈ 9.672412086

            assert(std::abs(9.672412 - cc.asd(idev, 2)) < prec);
        }

        {
            const auto response = cc.check(idev, {3, 15});

            assert(MSG_TYPE::COMMAND == response->type());
            assert(0 == dynamic_cast<const command*>(response.get())->value());

            // avg: (23 + 3 + 2 + 0) / 4 = 7
            // sum: (23 - 7)^2 + (3 - 7)^2 + (2 - 7)^2 + (0 - 7)^2 = 346
            // sqrt(346 / 4) = 9.300537

            assert(std::abs(9.300537 - cc.asd(idev, 3)) < prec);
        }
    }
}
