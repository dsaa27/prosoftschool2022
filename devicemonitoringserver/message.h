#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>
#include <iostream>



struct Message {

    virtual ~Message(){};

    enum TypeOfMessage {
        Meterage,
        Command,
        Error,
    };

};

struct Meterages : public Message {

    Meterages(uint64_t timeStampInput, uint8_t valueInput) {

        timeStamp = timeStampInput;
        value = valueInput;

    }
    ~Meterages(){};

    uint64_t timeStamp = 0; // Метка времени
    uint8_t value = 0; // измерение
    TypeOfMessage type = Meterage;


};

struct Commands : public Message {

    Commands(int correctionInput){
        correction = correctionInput;
    }


    int correction;
    TypeOfMessage type = Command;

};


struct Errors : public Message {

    TypeOfMessage type = Error;

};



#endif // MESSAGE_H
