#include "MathUtils.cpp"

#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class MathUtilsTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testXorUpto() {
        int64_t x = xorUpto(0);
        CPPUNIT_ASSERT_EQUAL(0LL, x);

        x = xorUpto(1);
        CPPUNIT_ASSERT_EQUAL(1LL, x);
        
        x = xorUpto(7);
        CPPUNIT_ASSERT_EQUAL(0LL, x);

        x = xorUpto(8);
        CPPUNIT_ASSERT_EQUAL(8LL, x);
    }

    CPPUNIT_TEST_SUITE(MathUtilsTest);
    CPPUNIT_TEST(testXorUpto);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathUtilsTest);
