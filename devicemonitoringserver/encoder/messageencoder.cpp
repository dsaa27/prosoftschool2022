#include <iostream>
#include <conio.h>
#include <encoder/messageencoder.h>


void MessageEncoder::SetEncodeAlgorithm (string NameOfAlgorithm)
{
    SelectedAlgorithm = NameOfAlgorithm;
}

string MessageEncoder::encode(const string& message)
{
    return AlgorithmMap[SelectedAlgorithm] -> encode(message);
}

string MessageEncoder::decode(const string& message)
{
    return AlgorithmMap[SelectedAlgorithm] -> decode(message);
}

string MessageEncoder::getname()
{
    return SelectedAlgorithm;
}

void MessageEncoder::NewAlgorithm (BaseEncoderExecutor & newAlgorithm){

    AlgorithmMap.map::insert(std::map<string, BaseEncoderExecutor*>::value_type(newAlgorithm.getname(),&newAlgorithm ));

}



