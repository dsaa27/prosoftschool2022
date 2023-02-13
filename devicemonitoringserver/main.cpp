#include "test_runner.h"
//#include "tests.h"
#include <servermock/servertests.h>
#include <message.h>

#include <messageserializator.h>




int main()
{

    TestRunner tr;

    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    std::cout << "Hello ept" << std::endl;

    Message * message1;
    Message * message2;

    Meterages meterage1(250,7);
    Meterages * pMet1 = &meterage1;

    Commands comand1(5);
    Commands *pCom1 = &comand1;

    message1 = pMet1;

    message2 = pCom1;

    MessageSerializator MET1;

    std:: cout << MET1.Serialize(message1) << std::endl;

    std::string HUI = MET1.Serialize(message1);
    std::string HUI2 = MET1.Serialize(message2);

    std::cout << MET1.Serialize(message2) << std::endl;

    //Meterages Meterage2;
    //Message * message3;

   // Meterages * Meterage2 = dynamic_cast<Meterages*>(MET1.DeSerialize(HUI));

   // std::cout <<"value is " << Meterage2->value << std::endl;

     //Meterage2 = MET1.DeSerialize(HUI);

    //std::cout << pMet1->type << std::endl;

    Message * pmessage = MET1.DeSerialize(HUI);

    Meterages * Meterage1 = dynamic_cast<Meterages*>(pmessage);

    std::cout << "timeStamp is " << Meterage1->timeStamp << "value is " << Meterage1->value << std::endl;

    Message * pmessage2 = MET1.DeSerialize(HUI2);

    Commands * Command1 = dynamic_cast<Commands*>(pmessage2);

    std::cout << "comand is " << Command1->correction << std::endl;









    //Temp.SetTypeOfMessage();
    //Temp.GetTypeOfMessage();

    // TODO: собственные тесты
    //RUN_TEST(tr, monitoringServerTest1);
    return 0;
}
