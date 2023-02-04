#include "commandcenter.h"
#include <vector>

/*
CommandCenter::CommandCenter()
{

}
*/

void CommandCenter::RegisterDevice(uint64_t& deviceId)
{
    Device NewDevice;

    //NewDevice.deviceId = deviceId;

    std::map <uint64_t, Device>::iterator  it = m_Device_Map.begin();

    for (int i=0; it != m_Device_Map.end(); it++, i++) //проверка на попытку регистрации устройства которое уже существует
    {
        if (it -> first == deviceId) return;
    }

    m_Device_Map[deviceId] = NewDevice;

    //m_Device_Vector.push_back(NewDevice);
}


void CommandCenter::SetSchedule(uint64_t& deviceId, DeviceWorkSchedule &Schedule)
{
    Device NewDevice;

    std::map <uint64_t, Device>::iterator  it = m_Device_Map.begin();

    for (int i=0; it != m_Device_Map.end(); it++, i++)
    {
        if (it->first == deviceId)
        {
            NewDevice = it->second;

            NewDevice.Schedule = Schedule;

            it->second = NewDevice;
        }
        else return; //такого устройства в командном центре не существует, необходимо провести регистрацию нового устройства
    }

    //std::map <uint64_t, Device>::iterator  it = m_Device_Map.find(deviceId);

}


void CommandCenter::GetMessage(uint64_t& deviceId, std::string &Message_fromServer, std::string &Message_toServer)
{
    uint8_t meterage_from_device = m_serialize->GetMeterage(Message_fromServer);
    uint64_t timeStamp_from_device = m_serialize->GetTimeStamp(Message_fromServer);

    if (m_Device_Map.count(deviceId) == 0)
    {
        Message_toServer = m_serialize->serialize_Message("NoSchedule");
    }

    std::map <uint64_t, Device>::iterator  it = m_Device_Map.find(deviceId);
    Device ExpDevice = it -> second;

    if (ExpDevice.expectedTimestamp > timeStamp_from_device)
    {
        ExpDevice.expectedTimestamp++;
        Message_toServer = m_serialize->serialize_Message("Obsolete");
    }
    else
    {

    const auto& Exp_schedule = ExpDevice.Schedule.schedule;

    uint64_t left = 0;
    uint64_t right = Exp_schedule.size()-1;
    uint64_t mid = (left+right)/2;


    while ((Exp_schedule[mid].timeStamp != timeStamp_from_device) && left < right)
        {
        if (Exp_schedule[mid].timeStamp < timeStamp_from_device) left = mid + 1;
        else right = mid - 1;
        mid = (left+right)/2;
        }

    if (Exp_schedule[mid].timeStamp != timeStamp_from_device)
        {
        ExpDevice.expectedTimestamp++;
        Message_toServer = m_serialize->serialize_Message("NoTimestamp");
        }
    else
        {

        double new_MSE = Exp_schedule[mid].value - meterage_from_device;

        ExpDevice.m_MSE[ExpDevice.expectedTimestamp] = new_MSE;

        ExpDevice.last_MSE = new_MSE;

        Message_toServer = m_serialize->serialize_Message(new_MSE); //отправка команды сервер и далее устройству

        ExpDevice.expectedTimestamp++;
        }
    }

    it -> second = ExpDevice;

    //delete ExpDevice;
}
