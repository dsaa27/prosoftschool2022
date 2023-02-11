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
