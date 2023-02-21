CXX:=/usr/bin/clang++

ser_test: \
	ser_test.o \
	ser.o \
	message_encoder.o \
	message.o
	$(CXX) \
	ser_test.o \
	ser.o \
	message.o \
	message_encoder.o \
	mul41.o \
	rot3.o \
	mirr.o \
	\
	-o ser_test

ser_test.o: ser_test.cxx
	$(CXX) \
	-c ser_test.cxx \
	\
	-o ser_test.o

ser.o: ser.cxx
	$(CXX) \
	-c ser.cxx \
	\
	-o ser.o

message.o: ../message/message.cxx
	$(CXX) \
	-c ../message/message.cxx \
	\
	-o message.o

message_encoder.o: \
	../encoding/message_encoder.cxx \
	mul41.o \
	rot3.o \
	mirr.o
	$(CXX) \
	-c ../encoding/message_encoder.cxx \
	\
	-o message_encoder.o

mul41.o: ../encoding/mul41/mul41.cxx
	$(CXX) \
	-c ../encoding/mul41/mul41.cxx \
	\
	-o mul41.o

rot3.o: ../encoding/rot3/rot3.cxx
	$(CXX) \
	-c ../encoding/rot3/rot3.cxx \
	\
	-o rot3.o

mirr.o: ../encoding/mirr/mirr.cxx
	$(CXX) \
	-c ../encoding/mirr/mirr.cxx \
	\
	-o mirr.o
