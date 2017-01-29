#include "Bitmask.cpp"

#include <vector>

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using boost::assign::list_of;

class BitmaskTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testPermutate() {
        const int N = 5;
        vector<int> result(5);

        result[0] = 7;
        for (int i = 1; i < N; i++) {
            result[i] = permutate(result[i-1]);
        }

        CPPUNIT_ASSERT(result == list_of(7)(11)(13)(14)(19));
    }

    void testPermutateEnd() {
        const int N = 5;
        vector<int> result(5);

        result[0] = 7;
        for (int i = 1; i < N; i++) {
            result[i] = permutate(result[i-1], 4);
        }

        CPPUNIT_ASSERT(result == list_of(7)(11)(13)(14)(-1));
    }

    CPPUNIT_TEST_SUITE(BitmaskTest);
    CPPUNIT_TEST(testPermutate);
    CPPUNIT_TEST(testPermutateEnd);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BitmaskTest);
