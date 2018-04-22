#include <bits/stdc++.h>

using namespace std;

#include "LinkCutTree.h"

#include <cppunit/extensions/HelperMacros.h>

class LinkCutTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testLinkCut() {
        LinkCutTree lct(5);
        for (int i = 1; i <= 5; i++) {
            lct.makeRoot(i);
        }
        for (int i = 1; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(i, lct.find(i));
        }
        lct.link(1, 2);
        lct.link(1, 3);
        lct.link(5, 4);
        vector<int> expected = {0, 3, 3, 3, 4, 4};
        for (int i = 1; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], lct.find(i));
        }

        lct.link(4, 3);
        lct.cut(3, 1);
        expected = {0, 1, 1, 3, 3, 3};
        for (int i = 1; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], lct.find(i));
        }
    }

    CPPUNIT_TEST_SUITE(LinkCutTreeTest);
    CPPUNIT_TEST(testLinkCut);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LinkCutTreeTest);

