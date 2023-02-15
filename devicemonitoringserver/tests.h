#ifndef TESTS_H
#define TESTS_H

#include <vector>
#include <iostream>
#include "deviceworkschedule.h"

// TODO: собственные тесты
/*!
 * \brief Тест сервера.
 */
void monitoringServerTest1();

void serialiserTest();

void encodeTestRO3();

void encodeTestMirror();

void encodeTestMultiply();

std::vector <double> generateExpectedHistory(std::vector <uint8_t>& meterage,std::vector<Phase> shedule);

#endif // TESTS_H
