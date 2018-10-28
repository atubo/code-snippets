#include <bits/stdc++.h>
using namespace std;

#include "data_structures/implicit_treap.h"

#include <cppunit/extensions/HelperMacros.h>

class ImplicitTreapTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testRangeQuery() {
        ImplicitTreap treap(5);
        vector<int> a = {0, 1, 4, 5, 2, 3};
        treap.build(a);
        CPPUNIT_ASSERT_EQUAL(9, treap.rangeQuery(2, 3));
        CPPUNIT_ASSERT_EQUAL(11, treap.rangeQuery(2, 4));
    }

    void testRangeUpdate() {
        ImplicitTreap treap(5);
        vector<int> a = {0, 1, 4, 5, 2, 3};
        treap.build(a);
        CPPUNIT_ASSERT_EQUAL(9, treap.rangeQuery(2, 3));

        treap.rangeUpdate(2, 4, 2);

        // 0 1 6 7 4 3
        CPPUNIT_ASSERT_EQUAL(13, treap.rangeQuery(2, 3));
        CPPUNIT_ASSERT_EQUAL(17, treap.rangeQuery(2, 4));
        CPPUNIT_ASSERT_EQUAL(18, treap.rangeQuery(1, 4));
    }

    void testGet() {
        ImplicitTreap treap(5);
        vector<int> a = {0, 1, 4, 5, 2, 3};
        treap.build(a);

        for (int i = 1; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(a[i], treap[i]);
        }
    }

    void testInsert() {
        ImplicitTreap treap(10);
        vector<int> a = {0, 2, 4};
        treap.build(a);
        vector<int> expected =  {0, 2, 4};
        for (int i = 1; i < (int)expected.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], treap[i]);
        }
        treap.insert(0, 1);
        // now 1, 2, 4
        expected = {0, 1, 2, 4};
        for (int i = 1; i < (int)expected.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], treap[i]);
        }

        treap.insert(3, 5);
        // now 1, 2, 4, 5
        expected = {0, 1, 2, 4, 5};
        for (int i = 1; i < (int)expected.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], treap[i]);
        }

        treap.insert(2, 3);
        // now 1, 2, 3, 4, 5
        expected = {0, 1, 2, 3, 4, 5};
        for (int i = 1; i < (int)expected.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], treap[i]);
        }
    }

    CPPUNIT_TEST_SUITE(ImplicitTreapTest);
    CPPUNIT_TEST(testRangeQuery);
    CPPUNIT_TEST(testRangeUpdate);
    CPPUNIT_TEST(testGet);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImplicitTreapTest);
