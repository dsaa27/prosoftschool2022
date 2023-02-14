#include <iostream>
#include <conio.h>
#include <encoder/messageencoder.h>


void MessageEncoder::SetEncodeAlgorithm (string NameOfAlgorithm)
{

    SelectedAlgorithm = NameOfAlgorithm;
}

string MessageEncoder::encode(string message)
{
    return AlgorithmMap[SelectedAlgorithm] -> encode(message);
}

string MessageEncoder::decode(string message)
{
    return AlgorithmMap[SelectedAlgorithm] -> decode(message);
}

string MessageEncoder::getname()
{
    return SelectedAlgorithm;
}

void MessageEncoder::NewAlgorithm (BaseEncoderExecutor & newAlgorithm){

    AlgorithmMap.map::emplace(newAlgorithm.getname(), &newAlgorithm);

}



