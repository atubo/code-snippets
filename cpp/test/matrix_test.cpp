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
    m.m_[0][0] = m.m_[0][1] = m.m_[1][0] = 1;

    Matrix ret = Matrix::power(m, 19);
    CPPUNIT_ASSERT_EQUAL(6765, ret.m_[0][0]);
    CPPUNIT_ASSERT_EQUAL(4181, ret.m_[0][1]);
    CPPUNIT_ASSERT_EQUAL(4181, ret.m_[1][0]);
    CPPUNIT_ASSERT_EQUAL(2584, ret.m_[1][1]);
  }

  CPPUNIT_TEST_SUITE(MatrixTest);
  CPPUNIT_TEST(testPower);
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);
