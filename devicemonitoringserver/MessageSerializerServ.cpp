#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#include "MessageSerializerServ.h"



    std::string CommandSerrializer::serializer()
    {
        std::string typMessage = "Command";
        int message = newMetrage;
        std::ostringstream message_in_str;
        message_in_str << typMessage << " " << message;
        return message_in_str.str();
    }




    
    std::string ErrorSerrializer::serializer(std::string message)
    {
        std::string typMessage = "Error";
        std::string errorName = message;
        std::ostringstream message_in_str;
        message_in_str << typMessage << " " << errorName;
        return message_in_str.str();
    }

    MeterageMessage messageDesirializer::deserialization(std::string message)
    {
        std::string messageTyp;
        MeterageMessage devvar;
        std::istringstream out(message);
        out >> messageTyp >> devvar.metrages >> devvar.timeStamp;
        return devvar;

    }
    std::string MessageSerializer::errorSerialization(std::string message)
    {
        ErrorSerrializer errorName;
        std::string serializedMessage = errorName.serializer(message);
        return serializedMessage;
    }
    std::string MessageSerializer::commandSerialization(int message)
    {
        CommandSerrializer command;
        command.newMetrage = message;
        std::string serializedMessage = command.serializer();
        return serializedMessage;
    }
    MeterageMessage MessageSerializer::deserialization(std::string message)
    {
        MeterageMessage metrages;
        return metrages = messageDesirializer::deserialization(message);
    }
