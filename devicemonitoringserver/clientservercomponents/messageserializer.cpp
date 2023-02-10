#include "messageserializer.h"

#include <vector>

std::string MessageSerializer::serializeMessage (const AbstractMessage& other)
{
    std::string stringAsMessage = other.convert2string();
    return stringAsMessage;
}

AbstractMessage* MessageSerializer::deserializeMessage (const std::string& messageAsString)
{
    using namespace Enumerations;
    checkInvalidDeserializeMessageArgument(messageAsString);
    std::istringstream istream(messageAsString);
    MessageType messageType;
    int currentInt;
    istream >> currentInt;
    messageType = static_cast<MessageType>(currentInt);
    if (messageType == MessageType::command) {
        double correction;
        istream >> correction;
        return dynamic_cast<AbstractMessage*>(new CommandMessage(correction));
    } else if (messageType == MessageType::error) {
        ErrorType errorType;
        istream >> currentInt;
        errorType = static_cast<ErrorType>(currentInt);
        return dynamic_cast<AbstractMessage*>(new ErrorMessage(errorType));
    } else {
        uint64_t timeStamp;
        int measureValue;
        istream >> timeStamp >> measureValue;
        return dynamic_cast<AbstractMessage*>(new MeterageMessage(timeStamp, static_cast<uint8_t>(measureValue)));
    }
}

void MessageSerializer::checkInvalidDeserializeMessageArgument(const std::string &messageAsString)
{
    try {
        using namespace Enumerations;
        bool flagInvalidArgument = false;

        std::istringstream istream(messageAsString);
        std::vector <std::string> messageSplitBySpace;
        std::string currentWord;
        while ( getline( istream, currentWord, ' ' ) ) {
          messageSplitBySpace.push_back(currentWord);
        }

        if (messageSplitBySpace.size() < 2)
            throw std::invalid_argument("");

        int messageTypeInt = std::stoi(messageSplitBySpace[0]);
        MessageType messageType = static_cast<MessageType>(messageTypeInt);

        if (messageType == MessageType::command) {
            double correction = std::stod(messageSplitBySpace[1]);
            if (    !((correction >= -1) && (correction <= 1))
                    ||
                    (messageSplitBySpace.size() > 2)) {
                flagInvalidArgument = true;
            }
        } else if (messageType == MessageType::error) {
            int errorTypeInt = std::stoi(messageSplitBySpace[1]);
            if (  !((errorTypeInt >= 1) && (errorTypeInt <= 3))
                  ||
                  (messageSplitBySpace.size() > 2)) {
                flagInvalidArgument = true;
            }
        } else if (messageType == MessageType::meterage) {
            if(messageSplitBySpace.size() < 3)
                throw std::invalid_argument("");
            std::stoull(messageSplitBySpace[1]);
            int measureValue = std::stoi(messageSplitBySpace[2]);
            if (    !((measureValue >= 0) && (measureValue <= 100))
                    ||
                    (messageSplitBySpace.size() > 3)) {
                flagInvalidArgument = true;
            }
        } else {
            flagInvalidArgument = true;
        }

        if(flagInvalidArgument)
            throw std::invalid_argument("");
    } catch (...) {
        throw std::invalid_argument("Deserializer has invalid argument");
    }

}
