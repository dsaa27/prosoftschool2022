#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#define multyplier 100.0
#define maxBufferSize 20
#include <cstdint>
#include <vector>
#include <unordered_map>
#include "message.h"

class DeviceWorkSchedule;
class CommandCenter;

struct Device {
    Device();
    ~Device();

    class MyBuffer {
    private:
        int* head = buffer;
        int buffer[maxBufferSize]{0};
        int tail{0};
    private:
        uint8_t maxSize{sizeof(buffer)/sizeof(int)};
    public:
        //добавить величину отклонения в кольцевой буфер
        void push(const int&);

    friend CommandCenter;
    };
    //последнее рассчитанное значение СКО для устройства
    double m_MSE;
    MyBuffer* m_errors;
    const DeviceWorkSchedule* m_deviceWorkSchedule = nullptr;
    uint64_t m_expectedTimestamp = 0;

friend CommandCenter;
};

class CommandCenter {
public:
    ~CommandCenter();
    //установить план работы устройства
    void setSchedule(const DeviceWorkSchedule& workSchedule);
    //вычислить СКО ошибки управления физическим параметром
    double getMSE(uint64_t deviceId) const;
    //вычислить корректировку
    Message* makeDecision(uint64_t deviceId, const Message* clientMeterage);

private:
    //вычислить СКО
    void calculateMSE(uint64_t deviceId) const;

private:
    std::unordered_map<uint64_t, Device*> m_devices;
};

#endif // COMMANDCENTER_H
