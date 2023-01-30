CXX := /usr/bin/clang++

mul41_test: mul41_test.o mul41.o
	$(CXX) mul41_test.o mul41.o -o mul41_test

mul41_test.o: mul41_test.cxx
	$(CXX) -c mul41_test.cxx -o mul41_test.o

mul41.o: mul41.cxx
	$(CXX) -c mul41.cxx -o mul41.o

mul41_test.cxx: mul41.hxx
mul41.cxx: mul41.hxx
mul41.hxx: ../base_encoder.hxx
