#ifndef DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
#define DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H


#include <string>
#include <sstream>
#include <cstring>

class MessageSerializator {
public:
    std::string serialize(std::string& message, std::ostringstream os, int messType, int errType = -1, int timeStamp = -1,
                          int value = -1) const
    {
        std::string result = "";
        switch (messType)
        {
            case messageType::Command:
                result.push_back(char(messageType::Command));
                result.push_back(' ');
                if (value > 100 || value < 0)
                    result.push_back(char(value));
                else return "";
                break;
            case messageType::Error:
                if (errType != -1)
                    return "";
                result.push_back(char(messageType::Error));
                result.push_back(char(errType));
                break;
            case messageType::Meterage:
                result.push_back(char(messageType::Meterage));
                result.push_back(' ');
                if (value > 100 || value < 0)
                    result.push_back(char(value));
                else return "";
                if (timeStamp != -1)
                    result.push_back(char(timeStamp));
                else return "";
                break;
            default:
                break;
        }
        return result;
    }

    std::string deserialize(std::string& message, std::ostringstream os) const
    {
        std::string result = "";
        std::string noDeserialized = os.str();
        os.clear();
        switch(int(noDeserialized[0]))
        {
            case messageType::Command:
                break;
            case messageType::Meterage:
                break;
            case messageType::Error:
                break;
            default:
                break;
        }
        //std::string els[3] = strtok(noDeserialized, " ");
        return result;
    }
private:
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
};



#endif //DEVICEMONITORINGSERVER_MESSAGESERIALIZATOR_H
