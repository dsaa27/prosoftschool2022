#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <devicemock.h>
#include <MessageSerializer.h>
#include <deviceworkschedule.h>


struct Device{

    uint64_t deviceId = 0;

    DeviceWorkSchedule Schedule;


};


class CommandCenter
{
public:
    //CommandCenter();

    void RegisterDevice (uint64_t deviceId);

    void GetMessage (std::string& Message_fromServer, std::string& Message_toServer);


    void GetSchedule (DeviceWorkSchedule& Schedule);




private:
    std::vector <Device> m_Device_Vector;
};







#endif // COMMANDCENTER_H
