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

#endif // TESTS_H
