CXX := /usr/bin/clang++

mirr_test: mirr_test.o mirr.o
	$(CXX) \
	mirr_test.o \
	mirr.o \
	\
	-o mirr_test

mirr_test.o: mirr_test.cxx
	$(CXX) \
	-c mirr_test.cxx \
	\
	-o mirr_test.o

mirr.o: mirr.cxx
	$(CXX) \
	-c mirr.cxx \
	\
	-o mirr.o

mirr_test.cxx: mirr.hxx
mirr.cxx: mirr.hxx
mirr.hxx: ../base_encoder.hxx
