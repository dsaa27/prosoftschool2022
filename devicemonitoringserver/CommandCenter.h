//
// Created by user on 23.01.2023.
//

#ifndef DEVICEMONITORINGSERVER_COMMANDCENTER_H
#define DEVICEMONITORINGSERVER_COMMANDCENTER_H


#include <cstdint>

class CommandCenter {
public:
    uint64_t compareMetarage(uint64_t meterage) {

    }
private:
    enum errorType
    {
        NoSchedule = 100,
        NoTimestamp = 101,
        Obsolete = 102
    };
};


#endif //DEVICEMONITORINGSERVER_COMMANDCENTER_H
