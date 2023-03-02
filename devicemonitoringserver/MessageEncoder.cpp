#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#include "MessageEncoder.h"

    std::string ROT3::encode(const std::string& message) const
    {
        std::string encodeMessage = message;
        char oneSymbol;
        for (int i = 0; encodeMessage[i]; i++)
        {
            oneSymbol = encodeMessage[i];
            oneSymbol += 3;
            encodeMessage[i] = oneSymbol;
        }
        return encodeMessage;
    }
    std::string  ROT3::decode(const std::string& message) const
    {
        std::string encodeMessage = message;
        char oneSymbol;
        for (int i = 0; encodeMessage[i]; i++)
        {
            oneSymbol = encodeMessage[i];
            oneSymbol -= 3;
            encodeMessage[i] = oneSymbol;
        }
        return encodeMessage;
    }
    std::string  ROT3::name() const
    {
        std::string name = "ROT3";
        return name;
    }

    std::string Mirror::encode(const std::string& message) const
    {
        std::string encodeMessage = message;
        std::string str_for_encode;
        for (int i = encodeMessage.size() - 1; i >= 0; i--)
        {
            str_for_encode = str_for_encode.append(1, encodeMessage[i]);
        }
        return str_for_encode;
    }
    std::string Mirror::decode(const std::string& message) const
    {
        std::string encodeMessage = message;
        std::string str_for_decode;
        for (int i = encodeMessage.size() - 1; i >= 0; i--)
        {
            str_for_decode = str_for_decode.append(1, encodeMessage[i]);
        }
        return str_for_decode;
    }
    std::string Mirror::name() const
    {
        std::string name = "Mirror";
        return name;
    }
    std::string Multiply41::encode(const std::string& message) const
    {
        std::string encodeMessage = message;
        char oneSymbol;
        std::string encodedMessage;
        for (int i = 0; encodeMessage[i]; i++)
        {
            oneSymbol = encodeMessage[i];

            uint16_t tSymbol = oneSymbol;
            tSymbol *= 41;
            encodedMessage += std::to_string(tSymbol);
        }
        return encodedMessage;
    }
    std::string Multiply41::decode(const std::string& message) const
    {
        std::string dencodeMessage = message;
        std::string dencodedMessage;
        for (int i = 0; dencodeMessage[i]; i += 4)
        {
            std::string exchVar = { dencodeMessage[i], dencodeMessage[i + 1], dencodeMessage[i + 2], dencodeMessage[i + 3] };
            int symbol = stoi(exchVar);
            symbol /= 41;
            char chSymbol = symbol;
            dencodedMessage += chSymbol;
        }
        return dencodedMessage;
    }
    std::string Multiply41::name() const
    {
        std::string name;
        return name;
    }


    MessageEncoder::MessageEncoder(std::map <std::string, BaseEncoderExecutor *> exctCnt)
    {
        exctCont = exctCnt;
    }
    std::string MessageEncoder::encode(const std::string& message)
    {
        return executor->encode(message);
    }
    std::string MessageEncoder::decode(const std::string& message)
    {
        return executor->decode(message);
    }
    void MessageEncoder::algChosser(std::string name)
    {
        executor = exctCont[name];
    }
    void MessageEncoder::algRegistr(std::string name, BaseEncoderExecutor *executor)
    {
        exctCont.insert(make_pair(name, executor));
    }
    MessageEncoder::~MessageEncoder() = default;
