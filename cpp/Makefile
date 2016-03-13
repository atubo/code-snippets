SRC:=$(wildcard *Test.cpp *test.cpp)
OBJ:=$(SRC:.cpp=.o)

unittest: $(OBJ)
	g++ -o $@ $^ -l cppunit

.cpp.o:
	g++ -c -std=c++0x $^

test: unittest
	./unittest

