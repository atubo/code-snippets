#include <bits/stdc++.h>

using namespace std;

#include "math/discrete_logarithm.h"

#include <cppunit/extensions/HelperMacros.h>

class DiscreteLogarithmTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        using discrete_logarithm::babystepGiantstep;
        int x = babystepGiantstep(3, 57, 113);
        CPPUNIT_ASSERT_EQUAL(100, x);

        x = babystepGiantstep(5, 35, 97);
        CPPUNIT_ASSERT_EQUAL(32, x);
    }

    CPPUNIT_TEST_SUITE(DiscreteLogarithmTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(DiscreteLogarithmTest);
