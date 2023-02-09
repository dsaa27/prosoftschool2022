#include "commandcenter.hxx"
#include "../deviceworkschedule.h"
#include <iostream>
#include "../message.hxx"
#include<cassert>
using namespace std;

int main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Test #1" << endl;
        const std::uint64_t idev{1000u};

        command_center cc{};
        const auto response = cc.check(idev, meterage{1u, 10u});

        assert(MSG_TYPE::ERROR == response->type());
        assert(ERR_TYPE::NOSCHEDULE == dynamic_cast<error*>(response.get())->err());
    }

    {
        cout << "Test #2" << endl;

        const std::uint64_t idev{1000u};
        const DeviceWorkSchedule schedule{.deviceId = idev,
                                    .schedule = {{0u, 43u}, {1u, 23u}, {2u, 10u}}};

        command_center cc{};
        cc.add(schedule);

        {
            const auto response = cc.check(idev, meterage(0u, 17u));

            assert(MSG_TYPE::COMMAND == response->type());
            assert(43u - 17u == dynamic_cast<command*>(response.get())->value());
        }

        {
            const auto response = cc.check(idev, meterage(1u, 41u));

            assert(MSG_TYPE::COMMAND == response->type());
            assert(23u - 41u == dynamic_cast<command*>(response.get())->value());
        }

        {
            const auto response = cc.check(idev, meterage(2u, 10u));

            assert(MSG_TYPE::COMMAND == response->type());
            assert(0u == dynamic_cast<command*>(response.get())->value());
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
        assert(ERR_TYPE::NOTIMESTAMP== dynamic_cast<error*>(response.get())->err());
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
            assert(23 - 81 == dynamic_cast<command*>(response.get())->value());
        }

        {
            const auto response = cc.check(idev, {0, 43});

            assert(MSG_TYPE::ERROR== response->type());
            assert(ERR_TYPE::OBSOLETE == dynamic_cast<error*>(response.get())->err());
        }

    }
}
