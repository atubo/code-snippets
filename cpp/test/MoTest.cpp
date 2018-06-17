#include <bits/stdc++.h>

using namespace std;

#include "Mo.h"

#include <cppunit/extensions/HelperMacros.h>

class MoTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        Mo mo(6, 6);
        mo.elem[0] = 1;
        mo.elem[1] = 1;
        mo.elem[2] = 2;
        mo.elem[3] = 1;
        mo.elem[4] = 2;
        mo.elem[5] = 3;
        mo.addQuery(0, 1, 1);
        mo.addQuery(0, 3, 1);
        mo.addQuery(1, 4, 1);
        mo.addQuery(2, 4, 2);
        mo.addQuery(2, 5, 2);
        mo.addQuery(0, 6, 3);

        mo.solve();

        vector<int> expected = {1, 2, 2, 1, 2, 1};
        for (int i = 0; i < 6; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], mo.ans[i]);
        }
    }

    CPPUNIT_TEST_SUITE(MoTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MoTest);



