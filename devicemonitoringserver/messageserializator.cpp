#include "messageserializator.h"
#include <sstream>
#include <vector>

std::string MessageSerializator::serialize(const Message* incoming) {
    std::ostringstream bufferout;
    if (auto* meterage = dynamic_cast<const Meterage*>(incoming)) {
        bufferout << std::to_string(meterage->m_type) << " ";
        bufferout << std::to_string(meterage->m_value) << " ";
        bufferout << std::to_string(meterage->m_timestamp);
    } else if (auto* command = dynamic_cast<const Command*>(incoming)) {
        bufferout << std::to_string(command->m_type) << " ";
        bufferout << std::to_string(command->m_value) << " ";
        bufferout << std::to_string(command->m_up);
    } else if (auto* error = dynamic_cast<const Error*>(incoming)) {
        bufferout << std::to_string(error->m_type) << " ";
        bufferout << std::to_string(error->m_errType);
    } else if (auto* info = dynamic_cast<const Info*>(incoming)) {
        bufferout << std::to_string(info->m_type) << " ";
        bufferout << info->m_message;
    }
    return bufferout.str();
}

Message* MessageSerializator::deserialize(const std::string& incoming) {
    std::istringstream buffer(incoming);

    std::vector<std::string> values;
    std::string temp_value;

    while (buffer) {
        buffer >> temp_value;
        values.push_back(temp_value);
    }
    if (values.at(0) == "0" || values.at(0) == "1" || values.at(0) == "2" || values.at(0) == "3") {
        switch (std::stoi(values.at(0))) {
        case 0: {
            auto* output = new Meterage;
            output->m_value = std::stoi(values.at(1));
            output->m_timestamp = std::stoi(values.at(2));
            return output;
            }
        case 1: {
            auto* output = new Command;
            output->m_value = std::stoi(values.at(1));
            output->m_up = static_cast<bool>(std::stoi(values.at(2)));
            return output;
            }
        case 2: {
            auto* output = new Error;
            output->m_errType = static_cast<Error::Type>(std::stoi(values.at(1)));
            return output;
            }
        case 3: {
            auto* output = new Info;
            auto iter = values.cbegin()+1;
            while (iter != values.cend()-2) {
                output->m_message += *iter;
                output->m_message += ' ';
                ++iter;
            }
            output->m_message += *(values.cend()-1);
            return output;
        }
        default: return nullptr;
        }
    } else return nullptr;
}
