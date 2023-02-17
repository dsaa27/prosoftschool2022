#include <iostream>
#include <sstream>
#include <string>
#include "MessageSerializerDev.h"




    MessageSerializer::MessageSerializer(uint8_t c_mesurment, uint16_t c_timeStamp)
	{
		mesurment = c_mesurment;
		timeStamp = c_timeStamp;
	}
	std::string MessageSerializer::serialization(uint8_t c_mesurment, uint16_t c_timeStamp)
	{
		std::string messageType = "Meterage";
		std::ostringstream message_in_str;
		message_in_str << messageType << " " << static_cast <int> (c_mesurment) << " " << c_timeStamp;
		return message_in_str.str();
	}
	std::string MessageSerializer::deserialization(const std::string& message)
	{
		std::istringstream out(message);
		std::string msType;
		std::string servMess;
		out >> msType;
		if (msType == "Error")
		{
			out >> servMess;
			return servMess;
		}
		else
		{
			uint64_t command;
			out >> command;
			return std::to_string(command);
		}
	}
	MessageSerializer::~MessageSerializer() = default;
