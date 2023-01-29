CXX := /usr/bin/clang++

mr_test: mr_test.o mr.o
	$(CXX) mr_test.o mr.o -o mr_test

mr_test.o: mr_test.cxx
	$(CXX) -c mr_test.cxx -o mr_test.o

mr.o: mr.cxx
	$(CXX) -c mr.cxx -o mr.o

mr_test.cxx: mr.hxx
mr.cxx: mr.hxx
mr.hxx: ../base_encoder.hxx
