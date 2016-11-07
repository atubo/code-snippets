SRC:=$(wildcard *Test.cpp *test.cpp)
OBJ:=$(SRC:.cpp=.o)
CXXFLAGS = -Wall -Wshadow -std=c++0x -gdwarf-2 -O0
LDFLAGS = -O0
DEPFILES:=$(patsubst %.cpp,%.d,$(SRC))


unittest: $(OBJ)
	g++ $(LDFLAGS) -o $@ $^ -l cppunit

%.o: %.cpp
	g++ -c $(CXXFLAGS) $<

%.d: %.cpp
	g++ $(CXXFLAGS) -MM $^ > $@

test: unittest
	./unittest

-include $(DEPFILES)
