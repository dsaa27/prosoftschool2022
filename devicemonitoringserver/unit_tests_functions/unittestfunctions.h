#ifndef UNITTESTFUNCTIONS_H
#define UNITTESTFUNCTIONS_H

#include <cstdint>
#include <string>
#include "../common.h"

void testMeasureMessageSerialization(uint64_t timeStamp, uint8_t measureValue, const std::string& expectSerializedMessage);

void testCommandMessageSerialization(double correction, const std::string& expectSerializedMessage);

void testErrorMessageSerialization(Enumerations::ErrorType errorType, const std::string& expectSerializedMessage);

void testMeasureMessageDeserialization(const std::string &messageAsString, uint64_t timeStamp, uint8_t measureValue);

void testCommandMessageDeserialization(const std::string &messageAsString, double correction);

void testErrorMessageDeserialization(const std::string &messageAsString, Enumerations::ErrorType errorType);

void testCheckInvalidDeserializeMessageArgument(const std::string &messageAsString, const std::string &exceptionMessage);
#endif // UNITTESTFUNCTIONS_H
