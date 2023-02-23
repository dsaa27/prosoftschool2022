#ifndef UNITTEST_H
#define UNITTEST_H

#include <cstdint>
#include <string>

#include "../clientservercomponents/message/abstractmessage.h"
#include "../clientservercomponents/commandcenter.h"

namespace unitTest
{
    void messageSerializer();

    void messageSerialization();

    void messageDeserialization();

    void messageEncoder();

    void commandCenter();

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

            void incorrectFormat();

            void catchInvalidArgumentException
                (CommandCenter &commandCenter, uint64_t deviceId,
                 std::string &receivedExceptionMessage, AbstractMessage *incorrectFormatMessage);
        }
    }
}
#endif // UNITTEST_H
