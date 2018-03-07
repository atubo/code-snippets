#include <bits/stdc++.h>

using namespace std;

#include "GomoryHuTree.h"

#include <cppunit/extensions/HelperMacros.h>

class GomoryHuTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testBuild() {
        GomoryHuTree ct(5);
        ct.addEdge(0, 2, 9);
        ct.addEdge(0, 4, 5);
        ct.addEdge(2, 4, 8);
        ct.addEdge(2, 3, 2);
        ct.build(0, 4);

        CPPUNIT_ASSERT(ct.edges[0][0] == make_pair(1, 0LL));
        CPPUNIT_ASSERT(ct.edges[0][1] == make_pair(2, 14LL));
        CPPUNIT_ASSERT(ct.edges[1][0] == make_pair(0, 0LL));
        CPPUNIT_ASSERT(ct.edges[2][0] == make_pair(0, 14LL));
        CPPUNIT_ASSERT(ct.edges[2][1] == make_pair(4, 13LL));
        CPPUNIT_ASSERT(ct.edges[3][0] == make_pair(4, 2LL));
        CPPUNIT_ASSERT(ct.edges[4][0] == make_pair(3, 2LL));
        CPPUNIT_ASSERT(ct.edges[4][1] == make_pair(2, 13LL));
    }

    CPPUNIT_TEST_SUITE(GomoryHuTreeTest);
    CPPUNIT_TEST(testBuild);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GomoryHuTreeTest);
