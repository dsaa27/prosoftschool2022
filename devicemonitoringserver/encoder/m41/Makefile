CXX := /usr/bin/clang++

m41_test: m41_test.o m41.o
	$(CXX) m41_test.o m41.o -o m41_test

m41_test.o: m41_test.cxx
	$(CXX) -c m41_test.cxx -o m41_test.o

m41.o: m41.cxx
	$(CXX) -c m41.cxx -o m41.o

m41_test.cxx: m41.hxx
m41.cxx: m41.hxx
m41.hxx: ../base_encoder.hxx
