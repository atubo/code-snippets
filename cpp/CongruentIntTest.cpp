#include "CongruentInt.cpp"

#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class CongruentIntTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testSelfMultiply() {
        CongruentInt x(2, 11);
        x *= 2;
        CPPUNIT_ASSERT((int64_t)x == 4);
        x *= 2;
        CPPUNIT_ASSERT((int64_t)x == 8);
        x *= 2;
        CPPUNIT_ASSERT((int64_t)x == 5);
    }

    CPPUNIT_TEST_SUITE(CongruentIntTest);
    CPPUNIT_TEST(testSelfMultiply);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CongruentIntTest);
