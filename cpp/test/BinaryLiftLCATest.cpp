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

        CPPUNIT_ASSERT(lca.depth == list_of(0)(1)(1)(2)(2)(2)(2));
        CPPUNIT_ASSERT(lca.father[0] == list_of(-1)(-1)(-1));
        CPPUNIT_ASSERT(lca.father[1] == list_of(0)(-1)(-1));
        CPPUNIT_ASSERT(lca.father[2] == list_of(0)(-1)(-1));
        CPPUNIT_ASSERT(lca.father[3] == list_of(1)(0)(-1));
        CPPUNIT_ASSERT(lca.father[4] == list_of(1)(0)(-1));
        CPPUNIT_ASSERT(lca.father[5] == list_of(2)(0)(-1));
        CPPUNIT_ASSERT(lca.father[6] == list_of(2)(0)(-1));

        CPPUNIT_ASSERT_EQUAL(0, lca.findLCA(0, 0));
        CPPUNIT_ASSERT_EQUAL(0, lca.findLCA(0, 4));
        CPPUNIT_ASSERT_EQUAL(1, lca.findLCA(1, 4));
        CPPUNIT_ASSERT_EQUAL(0, lca.findLCA(3, 5));
        CPPUNIT_ASSERT_EQUAL(1, lca.findLCA(3, 4));
    }

    CPPUNIT_TEST_SUITE(BinaryLiftLCATest);
    CPPUNIT_TEST(testLCA);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(BinaryLiftLCATest);
