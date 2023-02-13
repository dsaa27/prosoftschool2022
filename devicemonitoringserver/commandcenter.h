#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "message.h"
constexpr double multyplier = 100.0;
constexpr uint8_t maxBufferSize = 20;
//constexpr uint8_t maxBufferSize = 4;
const double zero = std::nan("0.0");

class DeviceWorkSchedule;
class CommandCenter;

struct Device {

    class MyBuffer {
    private:
    //public:
        int* head = &buffer[0];
        std::array<int,maxBufferSize> buffer{};
        int tail{0};
    private:
    //public:
        uint8_t maxIndex{sizeof(buffer)/sizeof(int) - 1};
    public:
        //добавить величину отклонения в кольцевой буфер
        void push(const int&);

    friend CommandCenter;
    };
    //последнее рассчитанное значение СКО для устройства
    double m_MSE;
    MyBuffer m_errors;
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
