#include <bits/stdc++.h>

using namespace std;

#include "UnionFindRB.h"

#include <cppunit/extensions/HelperMacros.h>

class UnionFindRBTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testUnionFind() {
        UnionFindRB uf(4);
        for (int i = 0; i < 4; i++) {
            CPPUNIT_ASSERT(uf.find(i) == i);
        }

        uf.joinCommit(0, 1);
        CPPUNIT_ASSERT(uf.find(0) == uf.find(1));
        CPPUNIT_ASSERT(uf.find(2) == 2);
        CPPUNIT_ASSERT(uf.find(3) == 3);

        uf.joinTentative(0, 2);
        CPPUNIT_ASSERT(uf.find(0) == uf.find(1) && uf.find(1) == uf.find(2));
        CPPUNIT_ASSERT(uf.find(3) == 3);

        uf.rollback();
        CPPUNIT_ASSERT(uf.find(0) == uf.find(1));
        CPPUNIT_ASSERT(uf.find(2) == 2);
        CPPUNIT_ASSERT(uf.find(3) == 3);

        uf.joinTentative(0, 2);
        uf.joinTentative(1, 3);
        for (int i = 1; i < 4; i++) {
            CPPUNIT_ASSERT(uf.find(i) == uf.find(0));
        }

        uf.rollback();
        CPPUNIT_ASSERT(uf.find(0) == uf.find(1));
        CPPUNIT_ASSERT(uf.find(2) == 2);
        CPPUNIT_ASSERT(uf.find(3) == 3);

        uf.resetCommitted();
        for (int i = 0; i < 4; i++) {
            CPPUNIT_ASSERT(uf.find(i) == i);
        }
    }

    CPPUNIT_TEST_SUITE(UnionFindRBTest);
    CPPUNIT_TEST(testUnionFind);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnionFindRBTest);
