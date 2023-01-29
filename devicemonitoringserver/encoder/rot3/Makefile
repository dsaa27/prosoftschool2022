CXX := /usr/bin/clang++

rot3_test: rot3_test.o rot3.o
	$(CXX) rot3_test.o rot3.o -o rot3_test

rot3_test.o: rot3_test.cxx
	$(CXX) -c rot3_test.cxx -o rot3_test.o

rot3.o: rot3.cxx
	$(CXX) -c rot3.cxx -o rot3.o

rot3_test.cxx: rot3.hxx
rot3.cxx: rot3.hxx
rot3.hxx: ../base_encoder.hxx
