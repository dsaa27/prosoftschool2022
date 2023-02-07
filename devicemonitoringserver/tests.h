#ifndef TESTS_H
#define TESTS_H


/*!
 * \brief Простой тест.
 */
void monitoringServerStandardTest();
/*!
 * \brief Тест отстутствия плана у устройства.
 */
void monitoringServerTestErrorNoSchedule();
/*!
 * \brief Тест отстутствия метки в плане.
 */
void monitoringServerTestErrorNoTimestamp();
/*!
 * \brief Тест нескольких случаев
 */
void monitoringServerTestComplex();
/*!
 * \brief Тест получения отрицательного значения для понижения физического параметра
 */
void monitoringServerTestNegativeValue();
/*!
 * \brief Тест подсчет СКО ошибки выполнения плана
 */
void monitoringServerTestStandardDeviation();

/*!
 * \brief Тест сервера с несколькими подключенным устройствами
 */
void monitoringServerTestTwoDevices();


/*!
 * \brief Общий тест шифровальщика
 */
void encodingTest();

/*!
 * \brief Тест метода шифрования Rot3
 *
 */
void encodingTestRot3();

/*!
 * \brief Тест метода шифрования Mirror
 */
void encodingTestMirror();

/*!
 * \brief Тест метода шифрования Multiply41
 */
void encodingTestMultiply41();

/*!
 * \brief Тест метода шифрования Xor
 */
void encodingTestXor();



#endif // TESTS_H
