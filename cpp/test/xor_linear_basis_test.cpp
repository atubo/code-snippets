#include <bits/stdc++.h>

using namespace std;

#include "xor_linear_basis.h"

#include <cppunit/extensions/HelperMacros.h>

class XorLinearBasisTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        XorLinearBasis lb(5);
        lb.insert(0);
        lb.insert(1);
        lb.insert(7);
        lb.insert(6);
        lb.insert(28);
        lb.insert(27);
        lb.insert(26);

        vector<int64_t> expected = {1, 0, 6, 0, 26, 0};
        for (int i = 0; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], lb.a[i]);
        }
    }

    CPPUNIT_TEST_SUITE(XorLinearBasisTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(XorLinearBasisTest);
