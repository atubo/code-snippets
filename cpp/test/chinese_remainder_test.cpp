#include <bits/stdc++.h>

using namespace std;

#include "math/chinese_remainder.h"

#include <cppunit/extensions/HelperMacros.h>

class ChineseRemainderTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        vector<int> m{3, 5, 7};
        math::ChineseRemainder cr(m);
        int x = cr.solve({2, 3, 2});
        CPPUNIT_ASSERT_EQUAL(23, x);
    }

    CPPUNIT_TEST_SUITE(ChineseRemainderTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ChineseRemainderTest);
