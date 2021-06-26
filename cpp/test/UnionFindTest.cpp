#include <bits/stdc++.h>

using namespace std;

#include "data_structures/UnionFind.h"

#include <cppunit/extensions/HelperMacros.h>

class UnionFindTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testUnionFind() {
        UnionFind uf(3);
        for (int i = 0; i < 3; i++) {
            CPPUNIT_ASSERT(uf.find(i) == i);
        }

        uf.join(1, 2);
        CPPUNIT_ASSERT(uf.find(1) == uf.find(2));
        CPPUNIT_ASSERT(uf.find(0) != uf.find(1));
    }

    void testSizeCount() {
        UnionFind uf(5);
        for (int i = 0; i < 5; i++) {
            CPPUNIT_ASSERT(uf.count(i) == 1);
        }
        uf.join(0, 1);
        CPPUNIT_ASSERT(uf.count(0) == 2);
        CPPUNIT_ASSERT(uf.count(1) == 2);
        CPPUNIT_ASSERT(uf.count(2) == 1);
        CPPUNIT_ASSERT(uf.count(3) == 1);
        CPPUNIT_ASSERT(uf.count(4) == 1);

        uf.join(3, 4);
        CPPUNIT_ASSERT(uf.count(0) == 2);
        CPPUNIT_ASSERT(uf.count(1) == 2);
        CPPUNIT_ASSERT(uf.count(2) == 1);
        CPPUNIT_ASSERT(uf.count(3) == 2);
        CPPUNIT_ASSERT(uf.count(4) == 2);

        uf.join(1, 2);
        CPPUNIT_ASSERT(uf.count(0) == 3);
        CPPUNIT_ASSERT(uf.count(1) == 3);
        CPPUNIT_ASSERT(uf.count(2) == 3);
        CPPUNIT_ASSERT(uf.count(3) == 2);
        CPPUNIT_ASSERT(uf.count(4) == 2);

        uf.join(0, 4);
        CPPUNIT_ASSERT(uf.count(0) == 5);
        CPPUNIT_ASSERT(uf.count(1) == 5);
        CPPUNIT_ASSERT(uf.count(2) == 5);
        CPPUNIT_ASSERT(uf.count(3) == 5);
        CPPUNIT_ASSERT(uf.count(4) == 5);
    }

    CPPUNIT_TEST_SUITE(UnionFindTest);
    CPPUNIT_TEST(testUnionFind);
    CPPUNIT_TEST(testSizeCount);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnionFindTest);
