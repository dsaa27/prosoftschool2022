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

        uint8_t buf3;
        output >> buf3;
        poutput = new Commands(buf3);

    } else if (type == 2) {

        TypeOfError errortype;
        int inputError;
        output >> inputError;

        switch (inputError){
            case 0:
                errortype = TypeOfError::NoShedule;
            case 1:
                errortype = TypeOfError::NoTimeStamp;
            case 2:
                errortype = TypeOfError::Obsolete;
        }
        poutput = new Errors(errortype);

    }
    return poutput;
}



