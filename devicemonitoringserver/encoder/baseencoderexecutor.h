#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H
#include <string>

/*!
 * \brief Базовый класс энкодера.
 */
class BaseEncoderExecutor
{
public:
    /*!
     * \brief Зашифровать строку.
     */
    virtual std::string encode(const std::string& message) = 0;
    /*!
     * \brief Расшифровать строку.
     */
    virtual std::string decode(const std::string& message) = 0;
    /*!
     * \brief Получить название алгоритма шифрования.
     */
    virtual std::string name() = 0;
};
#endif // BASEENCODEREXECUTOR_H
