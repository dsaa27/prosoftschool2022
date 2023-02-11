#ifndef UNITTEST_H
#define UNITTEST_H

#include <cstdint>
#include <string>

#include "../deviceworkschedule.h"

namespace unitTest
{
    void messageSerializer();

    void messageSerialization();

    void messageDeserialization();

    void messageEncoder();

    void commandCenter();

    void testCheckInvalidDeserializeMessageArgument();

    DeviceWorkSchedule* createRandomDeviceWorkSchedule();

    std::vector<uint8_t> createRandomMeterageVector(size_t vectorSize);

    void testCommandCenterReceiveAndSendMessage();

    void testCommandtMessage();

    void testErrorMessage();

    void testNoScheduleError();

    void testNoTimeStampError();

    void testObsoleteError();

    void testIncorrectFormatMessage();

    void testStandardDeviationCalculation();

    namespace serialization
    {
        void meterageMessage();

        void commandMessage();

        void errorMessage();
    }

    namespace deserialization
    {
        void meterageMessage();

        void commandMessage();

        void errorMessage();

        void invalidArgument();

        void catchInvalidArgumentException(
                std::string &receivedExceptionMessage,
                const std::string& wrongDeserializeMessage
                );
    }

    namespace codeAlgorithm
    {
        void ROT3Code();

        void Multiply41Code();

        void MirrorCode();

        void MixedCodeAlgorithms();

        void inductiveEncoding();
    }

    namespace commandCenterTask
    {
        void setUnsetDeviceWorkSchedule();

        void receiveAndSendMessage();

        void standardDeviationCalculation();

        double calculateStandardDeviation(double inaccuracy);

        namespace typeMessage
        {
            void command();

            void noScheduleError();

            void obsoleteError();

            void noTimeStampError();
        }
    }
}
#endif // UNITTEST_H
