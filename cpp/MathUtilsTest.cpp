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

    void testCountOnes() {
        int64_t x = countOnes(0);
        CPPUNIT_ASSERT_EQUAL(0LL, x);

        x = countOnes(1);
        CPPUNIT_ASSERT_EQUAL(1LL, x);

        x = countOnes(4);
        CPPUNIT_ASSERT_EQUAL(5LL, x);

        x = countOnes(9);
        CPPUNIT_ASSERT_EQUAL(15LL, x);
    }

    void testBinom() {
        Binom::generate(20);
        for (int i = 0; i <= 20; i++) {
            CPPUNIT_ASSERT_EQUAL(1, Binom::binom[i][0]);
            CPPUNIT_ASSERT_EQUAL(1, Binom::binom[i][i]);
        }
        CPPUNIT_ASSERT_EQUAL(21, Binom::binom[7][2]);
        CPPUNIT_ASSERT_EQUAL(21, Binom::binom[7][5]);
        CPPUNIT_ASSERT_EQUAL(1140, Binom::binom[20][3]);
    }

    CPPUNIT_TEST_SUITE(MathUtilsTest);
    CPPUNIT_TEST(testXorUpto);
    CPPUNIT_TEST(testCountOnes);
    CPPUNIT_TEST(testBinom);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathUtilsTest);
