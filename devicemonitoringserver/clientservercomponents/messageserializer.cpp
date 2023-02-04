#include "messageserializer.h"

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

        //stirng had to be at least 3 chars
        if (messageAsString.length() == 0)
            flagInvalidArgument = true;

        std::string beforeFirstSpace = messageAsString.substr(0, messageAsString.find(" "));
        std::string afterFirstSpace = "";

        //if ther is no " "
        if(messageAsString.length() == beforeFirstSpace.length()) {
            flagInvalidArgument = true;
        } else {
            afterFirstSpace = messageAsString.substr(messageAsString.find(" ") + 1);
        }

        int messageTypeInt = std::stoi(beforeFirstSpace);
        MessageType messageType = static_cast<MessageType>(messageTypeInt);

        if (messageType == MessageType::command) {
            double correction = std::stod(afterFirstSpace);
            if (!((correction >= 0) && (correction <= 1)))
                flagInvalidArgument = true;
        } else if (messageType == MessageType::error) {
            int errorTypeInt = std::stoi(afterFirstSpace);
            if (!((errorTypeInt >= 1) && (errorTypeInt <= 3)))
                flagInvalidArgument = true;
        } else if (messageType == MessageType::meterage) {
            std::string afterSecondSpace = "";

            //if there is no second " "
            if(afterFirstSpace.find(" ") == std::string::npos)
            {
                flagInvalidArgument = true;
            } else {
                afterSecondSpace = afterFirstSpace.substr(afterFirstSpace.find(" ") + 1);
            }

            std::stoull(afterFirstSpace.substr(0, afterFirstSpace.find(" ")));
            int measureValue = std::stoi(afterSecondSpace);
            if (!((measureValue >= 0) && (measureValue <= 100))
                    ||
                (afterSecondSpace.find(" ") != std::string::npos)) {
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
