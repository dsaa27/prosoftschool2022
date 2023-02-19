CXX:=/usr/bin/clang++

CXXFLAGS := \
	-Wall \
	-Wextra \
	-Werror \
	-Wpedantic \
	-std=c++20

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
	$(CXXFLAGS) \
	-c ../message/message.cxx \
	\
	-o message.o

commandcenter.o: commandcenter.cxx
	$(CXX) \
	$(CXXFLAGS) \
	-c commandcenter.cxx \
	\
	-o commandcenter.o

commandcenter_test.o: commandcenter_test.cxx
	$(CXX) \
	$(CXXFLAGS) \
	-c commandcenter_test.cxx \
	\
	-o commandcenter_test.o
