#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#include "deviceworkschedule.h"
#include "MessageEncoder.h"
#include "MessageSerializerServ.h"
#include "ComandCenter.h"

    std::string ComandCenter::comparisonWPlan(uint64_t deviceId, uint64_t m_timeStamp, uint8_t metrages)
    {
        uint64_t devId = deviceId;
        std::vector <Phase> plShedule = plan.schedule;
        Phase lastTimeStamp = plShedule.back();
        Phase firstTimeStamp = plShedule.front();
        if (devId != plan.deviceId)
        {
            std::string message = "NoSchedule";
            std::string serialMessage = MessageSerializer::errorSerialization(message);
            std::string encodedMessage = oEncCmd.encode(serialMessage);
            return encodedMessage;
        }
        else if (m_timeStamp > lastTimeStamp.timeStamp || m_timeStamp < firstTimeStamp.timeStamp)
        {
            std::string message = "NoTimestamp";
            std::string serialMessage = MessageSerializer::errorSerialization(message);
            std::string encodedMessage = oEncCmd.encode(serialMessage);
            return encodedMessage;
        
        }
        Phase phase = plShedule[m_timeStamp - 1];
        if (m_timeStamp < phase.timeStamp)
        {
            std::string message = "Obsole";
            std::string serialMessage = MessageSerializer::errorSerialization(message);
            std::string encodedMessage = oEncCmd.encode(serialMessage);
            return encodedMessage;
    
        }
        else
        {
            Phase pMetrages = plShedule[m_timeStamp - 1];
            if (metrages > pMetrages.value || metrages < pMetrages.value)
            {
                int command = pMetrages.value;
                std::string serialMessage = MessageSerializer::commandSerialization(command);
                std::string encodedMessage = oEncCmd.encode(serialMessage);
                ComandCenter forDeviation;
                forDeviation.plan = plan;
                sDeviation = forDeviation.s_deviation(metrages, m_timeStamp);
                return encodedMessage;
            
            }
            else
            {
                int command = 0;
                std::string serialMessage = MessageSerializer::commandSerialization(command);
                std::string encodedMessage = oEncCmd.encode(serialMessage);
                return encodedMessage;
                
            }
        }
    }
    void ComandCenter::setEncodingAlgoritm(std::string name)
    {
        oEncCmd.algChosser(name);
    }
    double ComandCenter::s_deviation(uint8_t metrages, uint64_t m_timeStamp)
    {
        std::vector <Phase> plShedule = plan.schedule;
        static std::vector <int> metrag; 
        Phase plPhase = plShedule[m_timeStamp-1];
        uint8_t plValue = plPhase.value;
        metrag.push_back(plValue - metrages);
        double valAverage = 0;
        for (int i = 0; i < metrag.size(); i++)
        {
            valAverage += metrag[i];
        }
        valAverage /= metrag.size();
        std::vector <double> vailInSq;
        for (int i = 0; i < metrag.size(); i++)
        {
            double val = metrag[i] - valAverage;
            vailInSq.push_back(val);
        }
        double summ= 0;
        for (int i = 0; i < vailInSq.size(); i++)
        {
            summ += vailInSq[i];
        }
        summ /= metrag.size();
        double sDeviation = sqrt(summ);
        return sDeviation;
    }
    double ComandCenter::getSDeviation()
    {
        return sDeviation;
    }
    ComandCenter::~ComandCenter() = default;
