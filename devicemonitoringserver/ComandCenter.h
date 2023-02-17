#ifndef COMANDCENTER_H
#define COMANDCENTER_H
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#include "deviceworkschedule.h"
#include "MessageEncoder.h"
#include "MessageSerializerServ.h"
class ComandCenter
{
public:
	DeviceWorkSchedule plan;
	MessageEncoder oEncCmd;
	double sDeviation;
	void setEncodingAlgoritm(std::string name);
	ComandCenter() = default;
	std::string comparisonWPlan(uint64_t deviceId, uint64_t m_timeStamp, uint8_t metrages);
	double getSDeviation();
	double s_deviation(uint8_t metrages, uint64_t m_timeStamp);
	~ComandCenter();
};


#endif //COMANDCENTER_H
