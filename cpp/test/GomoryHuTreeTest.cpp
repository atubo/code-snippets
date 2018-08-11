#include <bits/stdc++.h>

using namespace std;

#include "GomoryHuTree.h"

#include <cppunit/extensions/HelperMacros.h>

class GomoryHuTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testBuild() {
        GomoryHuTree ct(5, 4);
        ct.addEdge(0, 2, 9);
        ct.addEdge(0, 4, 5);
        ct.addEdge(2, 4, 8);
        ct.addEdge(2, 3, 2);
        ct.build();

        CPPUNIT_ASSERT(ct.edges[0][0] == make_pair(1, int64_t(0)));
        CPPUNIT_ASSERT(ct.edges[0][1] == make_pair(2, int64_t(14)));
        CPPUNIT_ASSERT(ct.edges[1][0] == make_pair(0, int64_t(0)));
        CPPUNIT_ASSERT(ct.edges[2][0] == make_pair(0, int64_t(14)));
        CPPUNIT_ASSERT(ct.edges[2][1] == make_pair(4, int64_t(13)));
        CPPUNIT_ASSERT(ct.edges[3][0] == make_pair(4, int64_t(2)));
        CPPUNIT_ASSERT(ct.edges[4][0] == make_pair(3, int64_t(2)));
        CPPUNIT_ASSERT(ct.edges[4][1] == make_pair(2, int64_t(13)));
    }

    CPPUNIT_TEST_SUITE(GomoryHuTreeTest);
    CPPUNIT_TEST(testBuild);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GomoryHuTreeTest);
