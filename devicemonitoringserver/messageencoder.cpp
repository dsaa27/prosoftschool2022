#include "messageencoder.h"


void EncoderROT3::encode(std::string& output, const std::string& input) {
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (input[i] == '0' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' ||
        input[i] == '5' || input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9') {
            int val = toInt(input[i]);
            output += std::to_string((val+3)%10);
        } else if (std::isupper(input[i])) {
            output += (input[i]-62)%26+65;
        } else {
            output += (input[i]-94)%26+97;
        }
    }
}
void EncoderROT3::decode(std::string& output, const std::string& input) {
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (input[i] == '0' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' ||
        input[i] == '5' || input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9') {
            int val = toInt(input[i]);
            output += std::to_string((val+7)%10);
        }  else if (std::isupper(input[i])) {
            output += ((input[i]-42)%26+65);
        } else {
            output += (input[i]-74)%26+97;
        }
    }
}

void EncoderMirror::encode(std::string& output, const std::string& input) {
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (input[i] == '0' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' ||
        input[i] == '5' || input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9') {
            int val = toInt(input[i]);
            output += std::to_string(9-val);
        } else if (std::isupper(input[i])) {
            output += 90-input[i]+65;
        } else {
            output += 122-input[i]+97;
        }
    }
}
void EncoderMirror::decode(std::string& output, const std::string& input) {
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == ' ')
            output += input[i];
        else if (input[i] == '0' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' ||
        input[i] == '5' || input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9') {
            int val = toInt(input[i]);
            output += std::to_string(9-val);
        } else if (std::isupper(input[i])) {
            output += 90-input[i]+65;
        } else {
            output += 122-input[i]+97;
        }
    }
}


void EncoderMultiply41::encode(std::string& output, const std::string& input) {
    for (uint8_t i = 0; i < input.size(); ++i) {
        if (input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' || input[i] == '5' ||
        input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9') {
            int val = toInt(input[i]);
            output += std::to_string(val*41);
        } else {output += input[i];}
    }
}
void EncoderMultiply41::decode(std::string& output, const std::string& input) {
    std::string substr("");
    for (uint8_t endstr = 0; endstr < input.size(); ++endstr) {
        substr = input[endstr];
        if  (substr == "1" || substr == "2" || substr == "3" || substr == "4" || substr == "5" ||
        substr == "6" || substr == "7" || substr == "8" || substr == "9") {
            substr += input[++endstr];
            uint16_t value = std::stoi(substr);
            if (value%41 == 0) {
                output += std::to_string(value/41);
                substr.clear();
            } else {
                substr += input[++endstr];
                value = std::stoi(substr);
                output += std::to_string(value/41);
                substr.clear();
            }
        } else output += substr;
    }
}

void EncoderCustom::encode (std::string& output, const std::string& input) {
    uint8_t j(0);
    for (uint8_t i = 0; i < input.size(); ++i) {
        output += key[j++]^input[i];
        if (j == key.size()) {
            j = 0;
        }
    }
}
void EncoderCustom::decode(std::string& output, const std::string& input) {
    uint8_t j(0);
    for (uint8_t i = 0; i < input.size(); ++i) {
        output += key[j++]^input[i];
        if (j == key.size()) {
            j = 0;
        }
    }
}
void EncoderCustom::setkey(const std::string& inputkey) {
    const uint8_t max_size (maxKeySize);
    if (inputkey == "") return;
    for (uint8_t i = 0u; i < (inputkey.size() < max_size ? inputkey.size() : max_size); ++i)
        key[i] = inputkey[i];
    key.resize((inputkey.size() < max_size ? inputkey.size() : max_size));
}


void MessageEncoder::proceedEncoding(std::string& output, const std::string& input) {
    if (!m_encoderexecutor) return;
    m_encoderexecutor->encode(output, input);
}

void MessageEncoder::proceedDecoding(std::string& output, const std::string& input) {
    if (!m_encoderexecutor) return;
    m_encoderexecutor->decode(output, input);
}

void MessageEncoder::selectMethod(Methods m_method) {
    if (m_encoderexecutor) delete m_encoderexecutor;
    switch (m_method) {
    case ROT3: {
        auto *encoder = new EncoderROT3;
        m_encoderexecutor = encoder;
        return;
        }
    case Mirror: {
        auto *encoder = new EncoderMirror;
        m_encoderexecutor = encoder;
        return;
        }
    case Multiply41: {
        auto *encoder = new EncoderMultiply41;
        m_encoderexecutor = encoder;
        return;
        }
    case Custom: {
        auto *encoder = new EncoderCustom;
        m_encoderexecutor = encoder;
        return;
        }
    default: return;
    }
}

void MessageEncoder::deselect() {
    if (m_encoderexecutor) {
        delete m_encoderexecutor;
        m_encoderexecutor=nullptr;
    }
    else return;
}

void MessageEncoder::registerСustom(const std::string& inputkey) {
    if (!dynamic_cast<EncoderCustom*>(m_encoderexecutor)) return;
    static_cast<EncoderCustom*>(m_encoderexecutor)->setkey(inputkey);
}

std::string MessageEncoder::getName() const {
    if (!m_encoderexecutor) return "No name";
    else return m_encoderexecutor->name();
}
