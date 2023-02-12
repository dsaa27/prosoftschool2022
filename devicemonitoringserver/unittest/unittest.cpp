#include "unittest.h"

#include <random>

void unitTest::messageSerializer()
{
    unitTest::messageSerialization();
    unitTest::messageDeserialization();
}

void unitTest::messageSerialization()
{
    serialization::meterageMessage();
    serialization::commandMessage();
    serialization::errorMessage();
}

void unitTest::messageDeserialization()
{
    deserialization::meterageMessage();
    deserialization::commandMessage();
    deserialization::errorMessage();
    deserialization::invalidArgument();
}

void unitTest::messageEncoder()
{
    codeAlgorithm::MirrorCode();
    codeAlgorithm::Multiply41Code();
    codeAlgorithm::ROT3Code();
    codeAlgorithm::MixedCodeAlgorithms();
    codeAlgorithm::inductiveEncoding();
}

void unitTest::commandCenter()
{
    commandCenterTask::setUnsetDeviceWorkSchedule();
    commandCenterTask::receiveAndSendMessage();
    commandCenterTask::standardDeviationCalculation();
}

void unitTest::commandCenterTask::receiveAndSendMessage()
{
    commandCenterTask::typeMessage::command();
    commandCenterTask::typeMessage::incorrectFormat();
    commandCenterTask::typeMessage::noScheduleError();
    commandCenterTask::typeMessage::noTimeStampError();
    commandCenterTask::typeMessage::obsoleteError();
}

