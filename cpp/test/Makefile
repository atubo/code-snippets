SRC:=$(wildcard *Test.cpp *test.cpp)
OBJ:=$(SRC:.cpp=.o)
CXXFLAGS = -Wall -Wshadow -std=c++0x -gdwarf-2 -O0 -I../src
LDFLAGS = -O0
DEPFILES:=$(patsubst %.cpp,%.d,$(SRC))


unittest: $(OBJ)
	g++ $(LDFLAGS) -o $@ $^ -l cppunit

%.o: %.cpp
	g++ -c $(CXXFLAGS) $<

%.d: %.cpp
	g++ $(CXXFLAGS) -MM $^ > $@.$$$$; \
	sed 's,\($*\)\.o[ :],\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

test: unittest
	./unittest

clean:
	rm *.o *.d unittest

-include $(DEPFILES)