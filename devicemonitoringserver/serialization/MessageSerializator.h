#ifndef DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
#define DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H


#include <string>
#include <sstream>
#include <cstring>

class MessageSerializator {
public:

    MessageSerializator();
    ~MessageSerializator();
    enum messageType
    {
        Meterage = 0,
        Command = 1,
        Error = 2
    };
    enum errorType
    {
        NoSchedule = 100,
        NoTimestamp = 101,
        Obsolete = 102
    };

    std::string serialize(messageType messType, uint64_t errType = -1, uint64_t timeStamp = -1,
                          uint64_t value = -1) const;
    std::string deserialize(const std::string& message) const;

};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
