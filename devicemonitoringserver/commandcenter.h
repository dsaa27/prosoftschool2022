#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#include <deviceworkschedule.h>
#include <message.h>
#include <map>

class CommandCenter
{
public:

    void setScheduleMap(const DeviceWorkSchedule& inputWorkSchedule);
    Message * createCommand(uint64_t deviceId, Meterages * message);
    //добавить расчет СКО
    //добавить запись в историю ошибок
private:
    std::map<uint64_t, std::vector<Phase>> ScheduleMap;

};

#endif // COMMANDCENTER_H
