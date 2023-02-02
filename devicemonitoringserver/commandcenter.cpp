#include "commandcenter.h"
#include <vector>

/*
CommandCenter::CommandCenter()
{

}
*/

void CommandCenter::RegisterDevice(uint64_t deviceId)
{
    Device NewDevice;

    NewDevice.deviceId = deviceId;

    //проверку на одинаковость deviceID

    m_Device_Vector.push_back(NewDevice);


}


void CommandCenter::GetSchedule(DeviceWorkSchedule &Schedule)
{
    //проверить ID девайса в плане и записать его в вектор
}
