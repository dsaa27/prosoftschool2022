#ifndef TESTS_H
#define TESTS_H

//Server test: single device, single measurement
void monitoringServerTest1();
//Server test: single device, single measurement, wrong encoding
void monitoringServerTest2();
//Server test: single device, multiple measurements
void monitoringServerTest3();
//Server test: single device, errors
void monitoringServerTest4();
//Server test: multiple devices, multiple measurements
void monitoringServerTest5();
//message encoder test
void encodingTest();
//message serializator test
void serializationTest();
//тест кольцевого буфера для хранения отклонений измерений для расчета СКО
//void BufferTest();

#endif // TESTS_H
