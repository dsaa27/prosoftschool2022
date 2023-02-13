#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H
#include <message.h>
//#include <string>

class MessageSerializator
{
public:
    MessageSerializator(){}
    ~MessageSerializator(){}

    std::string Serialize(Message * inputMessage);
    Message * DeSerialize(std::string inputMessage);

};




#endif // MESSAGESERIALIZATOR_H
