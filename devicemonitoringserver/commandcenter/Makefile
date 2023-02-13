CXX:=/usr/bin/clang++

commandcenter_test: \
	commandcenter.o \
	commandcenter_test.o
	$(CXX) \
		commandcenter.o \
		commandcenter_test.o \
		\
		-o commandcenter_test

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
