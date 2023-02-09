#ifndef UNITTESTFUNCTIONS_H
#define UNITTESTFUNCTIONS_H

#include <cstdint>
#include <string>

#include "../common.h"
#include "../deviceworkschedule.h"

namespace unitTestFunctions
{
    void testMessageSerialization();

    void testMessageDeserialization();

    void testMeasureMessageSerialization(uint64_t timeStamp, uint8_t measureValue, const std::string expectSerializedMessage);

    void testCommandMessageSerialization(double correction, const std::string expectSerializedMessage);

    void testErrorMessageSerialization(Enumerations::ErrorType errorType, const std::string expectSerializedMessage);

    void testMeasureMessageDeserialization(const std::string messageAsString, uint64_t timeStamp, uint8_t measureValue);

    void testCommandMessageDeserialization(const std::string messageAsString, double correction);

    void testErrorMessageDeserialization(const std::string messageAsString, Enumerations::ErrorType errorType);

    void testCheckInvalidDeserializeMessageArgument(const std::string messageAsString, const std::string exceptionMessage);

    DeviceWorkSchedule* createRandomDeviceWorkSchedule();

    std::vector<uint8_t> createRandomMeterageVector(size_t vectorSize);

    void testCommandCenterSetUnsetDeviceWorkSchedule();

    void testCommandCenterReceiveAndSendMessage();

    void testCommandtMessage();

    void testErrorMessage();

    void testNoScheduleError();

    void testNoTimeStampError();

    void testObsoleteError();

    void testIncorrectFormatMessage();

    void testStandardDeviationCalculation();
}
#endif // UNITTESTFUNCTIONS_H
