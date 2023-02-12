#include "messageencoder.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace
{

struct ROT3EncoderExecutor final : public BaseEncoderExecutor
{
    ~ROT3EncoderExecutor() final = default;

    std::string encode(const std::string& originString) final
    {
        std::stringstream ss;

        for (uint8_t now : originString) {
            ss << static_cast<uint8_t>(now + 3);
        }

        return ss.str();
    }

    std::string decode(const std::string& encodedString) final
    {
        std::stringstream ss;

        for (uint8_t now : encodedString) {
            ss << static_cast<uint8_t>(now - 3);
        }

        return ss.str();
    }

    std::string name() final
    {
        return "ROT3";
    }
};

struct MirrorEncoderExecutor final : public BaseEncoderExecutor
{
    ~MirrorEncoderExecutor() final = default;

    std::string encode(const std::string& originString) final
    {
        std::string encodedString = "";
        std::string currentCharAsIntString;

        for (uint8_t now : originString) {
            currentCharAsIntString = std::to_string(static_cast<int>(now));
            encodedString += mirrorWord(currentCharAsIntString) + " ";
        }
        encodedString.erase(encodedString.size() - 1); // erase last space \s

        return encodedString;
    }

    std::string decode(const std::string& encodedString) final
    {
        std::stringstream ss;

        std::istringstream istream(encodedString);
        std::string currentWord;
        while ( getline( istream, currentWord, ' ' ) )
            ss << static_cast<char>(std::stoi(mirrorWord(currentWord)));

        return ss.str();
    }

    std::string name() final
    {
        return "Mirror";
    }

private:
    std::string mirrorWord(const std::string &unmirroredWord)
    {
        std::string mirroredWord = unmirroredWord;

        if (mirroredWord.size() > 1)
            std::swap(mirroredWord[0], mirroredWord[unmirroredWord.size() - 1]);

        return mirroredWord;
    }
};

struct Multiply41EncoderExecutor final : public BaseEncoderExecutor
{
    ~Multiply41EncoderExecutor() final = default;

    std::string encode(const std::string& originString) final
    {
        std::stringstream ss;
        std::string currentMultipliedBy41Char;

        for (uint8_t now : originString) {
            currentMultipliedBy41Char = multiply41(static_cast<int>(now));
            ss << currentMultipliedBy41Char << " ";
        }

        return ss.str().erase(ss.str().size() - 1); //erase last space \s
    }

    std::string decode(const std::string& encodedString) final
    {
        std::stringstream ss;

        std::istringstream istream(encodedString);
        std::string currentWord;
        while ( getline( istream, currentWord, ' ' ) )
            ss << devide41(currentWord);

        return ss.str();
    }

    std::string name() final
    {
        return "Multiply41";
    }
private:
    std::string multiply41 (int charAsInt)
    {
        int multipliedBy41Int = charAsInt * 41;
        return std::to_string(multipliedBy41Int);
    }

    uint8_t devide41 (const std::string &intAsString)
    {
        int originInt = std::stoi(intAsString);
        originInt /= 41;
        return static_cast<uint8_t>(originInt);
    }
};

} //namespace

MessageEncoder::MessageEncoder()
{
    m_coderLibrary["ROT3"] = new ROT3EncoderExecutor;
    m_coderLibrary["Multiply41"] = new Multiply41EncoderExecutor;
    m_coderLibrary["Mirror"] = new MirrorEncoderExecutor;
}

MessageEncoder::~MessageEncoder()
{
    for (auto it = m_coderLibrary.cbegin(); it != m_coderLibrary.cend(); it++)
        delete it->second;
}

std::string MessageEncoder::encode (const std::string &originMessage)
{
    return m_chosenCodeAlgorithm->encode(originMessage);
}

std::string MessageEncoder::decode (const std::string &encodedMessage)
{
    return m_chosenCodeAlgorithm->decode(encodedMessage);
}

bool MessageEncoder::chooseCodingAlgorithm(const std::string &codingAlgorithmName)
{
   if (m_coderLibrary.find(codingAlgorithmName) != m_coderLibrary.end()) {
        m_chosenCodeAlgorithm = m_coderLibrary.find(codingAlgorithmName)->second;
        return true;
   } else {
       return false;
   }
}

void MessageEncoder::registrateNewAlgorithm(BaseEncoderExecutor *newCoder)
{
    std::string coderAlgorithmName = newCoder->name();
    m_coderLibrary[coderAlgorithmName] = newCoder;
}
