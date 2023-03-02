#ifndef MESSAGESERIALIZERDEV_H
#define MESSAGESERIALIZERDEV_H

#include <iostream>
#include <sstream>
#include <string>
struct MessageSerializer
{
    uint8_t mesurment;
    uint16_t timeStamp;
    MessageSerializer(uint8_t c_mesurment, uint16_t c_timeStamp);
    std::string serialization(uint8_t c_mesurment, uint16_t c_timeStamp);
    static std::string deserialization(const std::string& message);
    ~MessageSerializer();

};

#endif //MESSAGESERIALIZERDEV_H