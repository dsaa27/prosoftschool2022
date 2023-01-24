#ifndef DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
#define DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H


#include <string>
#include <sstream>
#include <cstring>
#include <vector>

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
        NoSchedule = 101,
        NoTimestamp = 102,
        Obsolete = 103
    };

    static std::string serialize(messageType messType, uint64_t errType = -1, uint64_t timeStamp = -1,
                          uint8_t value = -1) ;
    static std::vector<uint64_t> deserialize(const std::string& message) ;

};

#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
