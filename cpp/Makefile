SRC:=$(wildcard *Test.cpp *test.cpp)
OBJ:=$(SRC:.cpp=.o)
CXXFLAGS = -Wall -Wshadow -std=c++0x -gdwarf-2 -O0
LDFLAGS = -O0

unittest: $(OBJ)
	g++ $(LDFLAGS) -o $@ $^ -l cppunit

.cpp.o:
	g++ -c $(CXXFLAGS) $^

test: unittest
	./unittest

