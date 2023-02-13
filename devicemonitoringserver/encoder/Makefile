CXX := /usr/bin/clang++

message_encoder_test: \
	message_encoder_test.o \
	message_encoder.o \
	rot3.o \
	mul41.o \
	mirr.o

	$(CXX) \
	message_encoder_test.o \
	message_encoder.o \
	rot3.o \
	mul41.o \
	mirr.o \
	\
	-o message_encoder_test

message_encoder_test.o: message_encoder_test.cxx
	$(CXX) \
	-c message_encoder_test.cxx \
	\
	-o message_encoder_test.o

message_encoder.o: message_encoder.cxx
	$(CXX) \
	-c message_encoder.cxx \
	\
	-o message_encoder.o

mul41.o: mul41/mul41.cxx
	$(CXX) \
	-c mul41/mul41.cxx \
	\
	-o mul41.o

rot3.o: rot3/rot3.cxx
	$(CXX) \
	-c rot3/rot3.cxx \
	\
	-o rot3.o

mirr.o: mirr/mirr.cxx
	$(CXX) \
	-c mirr/mirr.cxx \
	\
	-o mirr.o
