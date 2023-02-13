#include "messageserializator.h"

#include <sstream>


std::string MessageSerializator::Serialize(Message * inputMessage)
{
    std::string output;

    if (Meterages * MeterageInput = dynamic_cast<Meterages*>(inputMessage)) {

        std::ostringstream MeterageOutput;
        MeterageOutput << MeterageInput->type << " " << MeterageInput->timeStamp << " " << int(MeterageInput->value) << " ";
        output = MeterageOutput.str();

    } else if (Commands * CommandInput = dynamic_cast<Commands*>(inputMessage)) {

        std::ostringstream CommandOutput;
        CommandOutput << CommandInput->type << " " << CommandInput->correction << " ";
        output = CommandOutput.str();

    } else if (Errors * ErrorInput = dynamic_cast<Errors*>(inputMessage)) {

        output = output;

    }

    return output;
}

Message * MessageSerializator::DeSerialize(std::string inputMessage) {
    std::istringstream output;
    short int type;

    output.str(inputMessage);

    output >> type;

    if (type == 0) {
        uint64_t buf1;
        uint8_t buf2;
        output >> buf1;
        output >> buf2;
        Message * pMet = new Meterages(buf1, buf2);

        return pMet;

    } else if (type == 1) {
        int buf3;
        output >> buf3;
        Message * pMet = new Commands(buf3);

        return pMet;
    }



}



