#include <bits/stdc++.h>

using namespace std;

#include "data_structures/sbt.h"

#include <cppunit/extensions/HelperMacros.h>

class SbtTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        Sbt sbt(5);
        sbt.insert(0);
        sbt.insert(3);
        sbt.insert(5);
        CPPUNIT_ASSERT_EQUAL(2, sbt.rank(4));
        sbt.insert(1);
        CPPUNIT_ASSERT_EQUAL(3, sbt.rank(4));
        sbt.insert(2);
        CPPUNIT_ASSERT_EQUAL(4, sbt.rank(4));
        CPPUNIT_ASSERT_EQUAL(0, sbt.rank(0));
    }

    CPPUNIT_TEST_SUITE(SbtTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SbtTest);
