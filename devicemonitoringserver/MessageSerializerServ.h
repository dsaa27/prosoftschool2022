#ifndef MESSAGESERIALIZERSERV_H
#define MESSAGESERIALIZERSERV_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#pragma once
struct CommandSerrializer
{
    int newMetrage;
    CommandSerrializer() = default;
    std::string serializer();
    ~CommandSerrializer() = default;
};
struct ErrorSerrializer
{
    std::string errorName;
    ErrorSerrializer () = default;
    std::string serializer(std::string message);
    ~ErrorSerrializer() = default;
};
struct MeterageMessage
{
    uint64_t timeStamp;
    MeterageMessage() = default;
    uint64_t metrages;
    ~MeterageMessage() = default;
};
struct messageDesirializer
{
    static MeterageMessage deserialization(std::string message);
};
struct MessageSerializer
{
    static std::string errorSerialization(std::string message);
    static std::string commandSerialization(int message);
    static MeterageMessage deserialization(std::string message);

};



#endif //MESSAGESERIALIZERSERV_H