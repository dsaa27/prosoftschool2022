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

        std::ostringstream ErrorOutput;
        ErrorOutput << ErrorInput->type << " " << ErrorInput->errorType<< " ";
        output = ErrorOutput.str();

    }

    return output;
}

Message * MessageSerializator::DeSerialize(std::string inputMessage) {

    std::istringstream output;
    short int type;
    Message * poutput;
    output.str(inputMessage);

    output >> type;

    if (type == 0) {

        uint64_t buf1;
        uint8_t buf2;
        output >> buf1;
        output >> buf2;
        poutput = new Meterages(buf1, buf2);

    } else if (type == 1) {

        int buf3;
        output >> buf3;
        poutput = new Commands(buf3);

    } else if (type == 2) {

        TypeOfError buf4;
        int buf5;
        output >> buf5;

        if (buf5 == 0) {
            buf4 = TypeOfError::NoShedule;
        } else if (buf5 == 1) {
            buf4 = TypeOfError::NoTimeStamp;
        } else buf4 = TypeOfError::Obsolete;

        poutput = new Errors(buf4);

    }
    return poutput;
}



