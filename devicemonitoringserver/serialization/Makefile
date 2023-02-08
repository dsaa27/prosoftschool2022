CXX:=/usr/bin/clang++

ser_test: ser_test.o ser.o
	$(CXX) ser_test.o ser.o -o ser_test

ser_test.o: ser_test.cxx
	$(CXX) -c ser_test.cxx -o ser_test.o

ser.o: ser.cxx
	$(CXX) -c ser.cxx -o ser.o
