#include <bits/stdc++.h>
using namespace std;

#include "BinaryLiftLCA.h"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class BinaryLiftLCATest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testLCA() {
        const int N = 7;
        BinaryLiftLCA lca(N, 0);
        lca.addEdge(0, 1);
        lca.addEdge(0, 2);
        lca.addEdge(1, 3);
        lca.addEdge(1, 4);
        lca.addEdge(2, 5);
        lca.addEdge(2, 6);

        lca.build();

        CPPUNIT_ASSERT(buildVec(lca.depth, 7) == list_of(0)(1)(1)(2)(2)(2)(2));
        CPPUNIT_ASSERT(buildVec(lca.father[0], 3) == list_of(-1)(-1)(-1));
        CPPUNIT_ASSERT(buildVec(lca.father[1], 3) == list_of(0)(-1)(-1));
        CPPUNIT_ASSERT(buildVec(lca.father[2], 3) == list_of(0)(-1)(-1));
        CPPUNIT_ASSERT(buildVec(lca.father[3], 3) == list_of(1)(0)(-1));
        CPPUNIT_ASSERT(buildVec(lca.father[4], 3) == list_of(1)(0)(-1));
        CPPUNIT_ASSERT(buildVec(lca.father[5], 3) == list_of(2)(0)(-1));
        CPPUNIT_ASSERT(buildVec(lca.father[6], 3) == list_of(2)(0)(-1));

        CPPUNIT_ASSERT_EQUAL(0, lca.findLCA(0, 0));
        CPPUNIT_ASSERT_EQUAL(0, lca.findLCA(0, 4));
        CPPUNIT_ASSERT_EQUAL(1, lca.findLCA(1, 4));
        CPPUNIT_ASSERT_EQUAL(0, lca.findLCA(3, 5));
        CPPUNIT_ASSERT_EQUAL(1, lca.findLCA(3, 4));
    }

    vector<int> buildVec(int *a, int n) {
        vector<int> ret;
        for (int i = 0; i < n; i++) {
            ret.push_back(a[i]);
        }
        return ret;
    }

    CPPUNIT_TEST_SUITE(BinaryLiftLCATest);
    CPPUNIT_TEST(testLCA);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BinaryLiftLCATest);
