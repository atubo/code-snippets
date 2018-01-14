#include <bits/stdc++.h>
using namespace std;

#include "Manacher.h"

#include <boost/assign/list_of.hpp>
#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class ManacherTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testManacher() {
        string s = "12212321";
        Manacher::manacher(s);
        vector<int> expected = list_of(-1)(1)(2)(1)(2)(5)(2)(1)(4)
            (1)(2)(1)(6)(1)(2)(1)(2)(1);
        for (int i = 1; i <(int)expected.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], Manacher::p[i]);
        }

        Manacher::calcMaxlen();
        vector<int> expected2 = list_of(4)(2)(3)(5)(3)(1)(1)(1);
        for (int i = 0; i < (int)s.length(); i++) {
            CPPUNIT_ASSERT_EQUAL(expected2[i], Manacher::maxlen[i]);
        }
    }

    CPPUNIT_TEST_SUITE(ManacherTest);
    CPPUNIT_TEST(testManacher);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ManacherTest);



