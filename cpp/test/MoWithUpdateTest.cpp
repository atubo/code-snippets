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
        vector<int> color = {0, 1, 2, 3, 4, 4};
        mo.color = color;
        mo.cnt = {0, 0, 0, 0, 0, 0};
        mo.addQuery(0, 4);
        mo.addQuery(1, 6);
        mo.addUpdate(0, 1, color[0]); color[0] = 1;
        mo.addQuery(0, 4);
        mo.addQuery(1, 6);
        mo.solve();
        CPPUNIT_ASSERT_EQUAL(4, (int)mo.ans.size());
        vector<int> expected{4, 4, 3, 4};
        CPPUNIT_ASSERT(mo.ans == expected);
    }

    void testMultipleUpdate() {
        MoWithUpdate mo(5);
        vector<int> color = {1, 2, 8, 4, 3};
        mo.color = color;
        mo.cnt = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        mo.addQuery(1, 5);
        mo.addUpdate(1, 7, color[1]); color[1] = 7;
        mo.addUpdate(3, 5, color[3]); color[3] = 5;
        mo.addQuery(2, 5);
        mo.addUpdate(0, 0, color[0]); color[0] = 0;
        mo.addUpdate(3, 3, color[3]); color[3] = 3;
        mo.addQuery(0, 4);
        mo.solve();
        vector<int> expected{4, 3, 4};
        CPPUNIT_ASSERT(mo.ans == expected);
    }

    void testReverseUpdate() {
        MoWithUpdate mo(5);
        vector<int> color = {2, 5, 5, 4, 6};
        mo.color = color;
        mo.cnt = {0, 0, 0, 0, 0, 0, 0};
        mo.addQuery(0, 4);
        mo.addUpdate(3, 1, color[3]); color[3] = 1;
        mo.addUpdate(1, 0, color[1]); color[1] = 0;
        mo.addQuery(1, 2);
        mo.addUpdate(4, 3, color[4]); color[4] = 3;
        mo.addQuery(1, 5);
        mo.addQuery(1, 2);
        mo.solve();
        vector<int> expected{3, 1, 4, 1};
        CPPUNIT_ASSERT(mo.ans == expected);
    }

    CPPUNIT_TEST_SUITE(MoWithUpdateTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST(testMultipleUpdate);
    CPPUNIT_TEST(testReverseUpdate);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MoWithUpdateTest);
