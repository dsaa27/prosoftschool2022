CXX:=/usr/bin/clang++

commandcenter_test: \
	commandcenter.o \
	commandcenter_test.o \
	message.o
	$(CXX) \
	commandcenter.o \
	commandcenter_test.o \
	message.o \
	\
	-o commandcenter_test

message.o: ../message/message.cxx
	$(CXX) \
	-c ../message/message.cxx \
	\
	-o message.o

commandcenter.o: commandcenter.cxx
	$(CXX) \
	-c commandcenter.cxx \
	\
	-o commandcenter.o

commandcenter_test.o: commandcenter_test.cxx
	$(CXX) \
	-c commandcenter_test.cxx \
	\
	-o commandcenter_test.o
