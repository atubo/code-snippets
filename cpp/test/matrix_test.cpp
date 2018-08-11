#include <bits/stdc++.h>

using namespace std;

#include "math/matrix.h"

#include <cppunit/extensions/HelperMacros.h>

class MatrixTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testPower() {
        Matrix m(2);
        m._m[0][0] = m._m[0][1] = m._m[1][0] = 1;

        Matrix ret = Matrix::power(m, 19);
        CPPUNIT_ASSERT_EQUAL(6765, ret._m[0][0]);
        CPPUNIT_ASSERT_EQUAL(4181, ret._m[0][1]);
        CPPUNIT_ASSERT_EQUAL(4181, ret._m[1][0]);
        CPPUNIT_ASSERT_EQUAL(2584, ret._m[1][1]);
    }

    CPPUNIT_TEST_SUITE(MatrixTest);
    CPPUNIT_TEST(testPower);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);
