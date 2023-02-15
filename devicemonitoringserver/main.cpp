#include "test_runner.h"
//#include "tests.h"
#include <servermock/servertests.h>
#include <message.h>

#include <messageserializator.h>
#include <encoder/messageencoder.h>



int main()
{

    TestRunner tr;

    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

//    std::cout << "Hello" << std::endl;

//    Message * message1;
//    Message * message2;

//    Meterages meterage1(250,7);
//    Meterages * pMet1 = &meterage1;

//    Commands comand1(5);
//    Commands *pCom1 = &comand1;

//    message1 = pMet1;

//    message2 = pCom1;

//    MessageSerializator MET1;
//    string mes1 = MET1.Serialize(message1);

//    std:: cout <<"serialized 1 message - " << mes1 << std::endl;

//    MessageEncoder Encoder1;

//    Encoder1.SetEncodeAlgorithm("Multiply41");
//    string encodemes1 = Encoder1.encode(mes1);
//    std::cout << "encoded 1 message - " << encodemes1 << std::endl;
//    string decodemes1 = Encoder1.decode(encodemes1);
//    std::cout << "decoded 1 message - " << decodemes1 << std::endl;




//    std::string H = MET1.Serialize(message1);
//    std::string H2 = MET1.Serialize(message2);

//    std::cout << "serialized 2 message - " << MET1.Serialize(message2) << std::endl;



//    Meterages Meterage2;
//    Message * message3;

//    Meterages * Meterage2 = dynamic_cast<Meterages*>(MET1.DeSerialize(HUI));

//    std::cout <<"value is " << Meterage2->value << std::endl;

//     Meterage2 = MET1.DeSerialize(HUI);

//    std::cout << pMet1->type << std::endl;

//    Message * pmessage = MET1.DeSerialize(H);

//    Meterages * Meterage1 = dynamic_cast<Meterages*>(pmessage);

//    std::cout << "timeStamp is " << Meterage1->timeStamp << "value is " << Meterage1->value << std::endl;

//    Message * pmessage2 = MET1.DeSerialize(H2);

//    Commands * Command1 = dynamic_cast<Commands*>(pmessage2);

//    std::cout << "comand is " << Command1->correction << std::endl;

//    Message * message3;
//    Errors err1(NoTimeStamp);
//    Errors *pErr1 = &err1;

//    message3 = pErr1;

//    string err = MET1.Serialize(message3);

//    std::cout << "serialized 3 message - " << err << std::endl;

//    Message * pError = MET1.DeSerialize(err);

//    Errors * pError1 = dynamic_cast<Errors*>(pError);

//    std::cout << "Type of message is " << pError1->type << "Type of Error is " << pError1->errorType << std::endl;













    //Temp.SetTypeOfMessage();
    //Temp.GetTypeOfMessage();

    // TODO: собственные тесты
    //RUN_TEST(tr, monitoringServerTest1);
    return 0;
}
