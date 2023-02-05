#include "messageencoder.h"

int BaseEncoderExecutor::toInt(const char& charToInt) {
    return charToInt-'0';
}


std::string EncoderROT3::encode(const std::string& input) {
    std::string output;
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (std::isdigit(input[i])) {
            int val = toInt(input[i]);
            output += std::to_string((val+3)%10);
        } else if (std::isupper(input[i])) {
            output += (input[i]-62)%26+65;
        } else {
            output += (input[i]-94)%26+97;
        }
    }
    return output;
}
std::string EncoderROT3::decode(const std::string& input) {
    std::string output;
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (std::isdigit(input[i])) {
            int val = toInt(input[i]);
            output += std::to_string((val+7)%10);
        }  else if (std::isupper(input[i])) {
            output += ((input[i]-42)%26+65);
        } else {
            output += (input[i]-74)%26+97;
        }
    }
    return output;
}

std::string EncoderMirror::encode(const std::string& input) {
    std::string output;
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (std::isdigit(input[i])) {
            int val = toInt(input[i]);
            output += std::to_string(9-val);
        } else if (std::isupper(input[i])) {
            output += 90-input[i]+65;
        } else {
            output += 122-input[i]+97;
        }
    }
    return output;
}
std::string EncoderMirror::decode(const std::string& input) {
    std::string output;
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (std::isdigit(input[i])) {
            int val = toInt(input[i]);
            output += std::to_string(9-val);
        } else if (std::isupper(input[i])) {
            output += 90-input[i]+65;
        } else {
            output += 122-input[i]+97;
        }
    }
    return output;
}


std::string EncoderMultiply41::encode(const std::string& input) {
    std::string output;
    for (uint8_t i = 0; i < input.size(); ++i) {
        int val = input[i]*41;
        int first = val/100;
        int second = val%100;
        output += first;
        output += second;
    }
    return output;
}
std::string EncoderMultiply41::decode(const std::string& input) {
    std::string output;
    for (uint8_t i = 0; i < input.size(); ++i) {
        int first = input[i++];
        int second = input[i];
        int val = (first*100+second)/41;
        output += val;
    }
    return output;
}

std::string EncoderCustom::encode (const std::string& input) {
    std::string output;
    uint8_t j(0);
    for (uint8_t i = 0; i < input.size(); ++i) {
        output += key[j++]^input[i];
        if (j == key.size()) {
            j = 0;
        }
    }
    return output;
}
std::string EncoderCustom::decode(const std::string& input) {
    std::string output;
    uint8_t j(0);
    for (uint8_t i = 0; i < input.size(); ++i) {
        output += key[j++]^input[i];
        if (j == key.size()) {
            j = 0;
        }
    }
    return output;
}
void EncoderCustom::setkey(const std::string& inputkey) {
    const uint8_t max_size (maxKeySize);
    if (inputkey == "")
        return;
    for (uint8_t i = 0u; i < (inputkey.size() < max_size ? inputkey.size() : max_size); ++i)
        key[i] = inputkey[i];
    key.resize((inputkey.size() < max_size ? inputkey.size() : max_size));
}

MessageEncoder::~MessageEncoder() {
    if (!m_encoderExecutors.empty()) {
        for (const auto& it : m_encoderExecutors)
            delete it.second;
    }
}

std::string MessageEncoder::proceedEncoding(const std::string& input) {
    if (!m_encoderexecutor)
        return input;
    return m_encoderexecutor->encode(input);
}

std::string MessageEncoder::proceedDecoding(const std::string& input) {
    if (!m_encoderexecutor)
        return input;
    return m_encoderexecutor->decode(input);
}

void MessageEncoder::selectMethod(const std::string& name) {
    if (name == "") {
        deselect();
    } else if (name == "ROT3") {
        if (m_encoderExecutors.count(name) == 0) {
            m_encoderExecutors.insert(std::make_pair(name, new EncoderROT3));
        }
        m_encoderexecutor = m_encoderExecutors[name];
    } else if (name == "Mirror") {
        if (m_encoderExecutors.count(name) == 0) {
            m_encoderExecutors.insert(std::make_pair(name, new EncoderMirror));
        }
        m_encoderexecutor = m_encoderExecutors[name];
    } else if (name == "Multiply41") {
        if (m_encoderExecutors.count(name) == 0) {
            m_encoderExecutors.insert(std::make_pair(name, new EncoderMultiply41));
        }
        m_encoderexecutor = m_encoderExecutors[name];
    } else {
        if (m_encoderExecutors.count(name) == 0) {
            deselect();
            return;
        } else {
            m_encoderexecutor = m_encoderExecutors[name];
        }
    }
    return;
}

void MessageEncoder::deselect() {
    m_encoderexecutor = nullptr;
}

void MessageEncoder::registerСustom(const std::string& name, const std::string& inputkey) {
    if (m_encoderExecutors.count(name) == 0) {
        m_encoderExecutors.insert(std::make_pair(name, new EncoderCustom(name)));
        static_cast<EncoderCustom*>(m_encoderExecutors[name])->setkey(inputkey);
    } else
        static_cast<EncoderCustom*>(m_encoderExecutors[name])->setkey(inputkey);
}

std::string MessageEncoder::getName() const {
    if (!m_encoderexecutor)
        return "No name";
    else
        return m_encoderexecutor->name();
}
