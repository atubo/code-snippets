#include <bits/stdc++.h>

using namespace std;

#include "MoWithUpdate.h"

#include <cppunit/extensions/HelperMacros.h>

class MoWithUpdateTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        MoWithUpdate mo(6);
        mo.color = {0, 1, 2, 3, 4, 4};
        mo.cnt = {0, 0, 0, 0, 0, 0};
        mo.addQuery(0, 4);
        mo.addQuery(1, 6);
        mo.addUpdate(0, 1);
        mo.addQuery(0, 4);
        mo.addQuery(1, 6);
        mo.solve();
        CPPUNIT_ASSERT_EQUAL(4, (int)mo.ans.size());
        vector<int> expected{4, 4, 3, 4};
        CPPUNIT_ASSERT(mo.ans == expected);
    }

    CPPUNIT_TEST_SUITE(MoWithUpdateTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MoWithUpdateTest);
