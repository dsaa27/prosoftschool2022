CXX := /usr/bin/clang++

test: \
	main.o \
	tests.o\
	devicemock.o \
	devicemonitoringserver.o \
	clientconnectionmock.o \
	connectionchannel.o \
	connectionmock.o \
	connectionservermock.o \
	taskqueue.o \
	object.o \
	commandcenter.o \
	serializator.o \
	message.o \
	servertests.o \
	encoder.o \
	rot3.o \
	mul41.o \
	mirr.o
	$(CXX) \
	main.o \
	tests.o \
	devicemock.o \
	devicemonitoringserver.o \
	clientconnectionmock.o \
	connectionchannel.o \
	connectionmock.o \
	connectionservermock.o \
	taskqueue.o \
	servertests.o \
	object.o \
	commandcenter.o \
	serializator.o \
	message.o \
	encoder.o \
	rot3.o \
	mul41.o \
	mirr.o \
	\
	-o test

main.o: main.cpp
	$(CXX) -c main.cpp -o main.o

tests.o: tests.cpp
	$(CXX) -c tests.cpp -o tests.o

devicemock.o: devicemock.cpp
	$(CXX) -c devicemock.cpp -o devicemock.o

devicemonitoringserver.o: devicemonitoringserver.cpp
	$(CXX) -c devicemonitoringserver.cpp -o devicemonitoringserver.o

clientconnectionmock.o: servermock/clientconnectionmock.cpp
	$(CXX) -c servermock/clientconnectionmock.cpp -o clientconnectionmock.o

connectionchannel.o: servermock/connectionchannel.cpp
	$(CXX) -c servermock/connectionchannel.cpp -o connectionchannel.o

connectionmock.o: servermock/connectionmock.cpp
	$(CXX) -c servermock/connectionmock.cpp -o connectionmock.o

connectionservermock.o: servermock/connectionservermock.cpp
	$(CXX) -c servermock/connectionservermock.cpp -o connectionservermock.o

object.o: servermock/object.cpp
	$(CXX) -c servermock/object.cpp -o object.o

taskqueue.o: servermock/taskqueue.cpp
	$(CXX) -c servermock/taskqueue.cpp -o taskqueue.o

commandcenter.o: commandcenter/commandcenter.cxx
	$(CXX) -c commandcenter/commandcenter.cxx -o commandcenter.o

serializator.o: serialization/ser.cxx
	$(CXX) -c serialization/ser.cxx -o serializator.o

message.o: message/message.cxx
	$(CXX) -c message/message.cxx -o message.o

encoder.o: encoder/message_encoder.cxx
	$(CXX) -c encoder/message_encoder.cxx -o encoder.o

mul41.o: encoder/mul41/mul41.cxx
	$(CXX) -c encoder/mul41/mul41.cxx -o mul41.o

mirr.o: encoder/mirr/mirr.cxx
	$(CXX) -c encoder/mirr/mirr.cxx -o mirr.o

rot3.o: encoder/rot3/rot3.cxx
	$(CXX) -c encoder/rot3/rot3.cxx -o rot3.o
