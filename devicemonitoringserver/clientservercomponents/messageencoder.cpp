#include "messageencoder.h"

#include <stdexcept>

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

void MessageEncoder::chooseCodingAlgorithm(const std::string& codeName)
{
   if (m_coderLibrary.find(codeName) != m_coderLibrary.end()) {
        m_chosenCodeAlgorithm = m_coderLibrary.find(codeName)->second;
   } else {
       throw std::invalid_argument("choseeCodingAlgorithm() had invalid argument");
   }
}

void MessageEncoder::registrateNewAlgorithm(BaseEncoderExecutor* newCoder)
{
    std::string coderAlgorithmName = newCoder->name();
    m_coderLibrary[coderAlgorithmName] = newCoder;
}
