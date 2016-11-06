#include <bits/stdc++.h>

using namespace std;

#include "UnionFind.cpp"

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

    CPPUNIT_TEST_SUITE(UnionFindTest);
    CPPUNIT_TEST(testUnionFind);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnionFindTest);
