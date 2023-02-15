#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H

#include <string>


/*!
 * \brief Базовый шифровальщика.
 */
class BaseEncoderExecutor
{
public:

    /*!
     * \brief Обработчик сообщения, которое нужно закодировать.
     */
    virtual std::string encode(std::string &message) = 0;

    /*!
     * \brief Обработчик сообщения, которое нужно раскодировать.
     */
    virtual std::string decode(std::string &message) = 0;

    /*!
     * \brief Возврат названия использованного алгоритма шифрования.
     */
    virtual std::string name_of_encode_algorithm() = 0;

};
#endif // BASEENCODEREXECUTOR_H
