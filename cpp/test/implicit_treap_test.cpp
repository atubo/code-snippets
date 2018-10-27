#include <bits/stdc++.h>
#include "data_structures/implicit_treap.h"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using boost::assign::list_of;
using namespace ImplicitTreap;

class ImplicitTreapTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}


    void testRangeQuery() {
        vector<int> a = list_of(1)(4)(5)(2)(3);
        NodePtr root = build_treap(a);
        CPPUNIT_ASSERT_EQUAL(9, ImplicitTreap::range_query(root, 1, 2));
        CPPUNIT_ASSERT_EQUAL(11, ImplicitTreap::range_query(root, 1, 3));
    }

    void testRangeUpdate() {
        vector<int> a = list_of(1)(4)(5)(2)(3);
        NodePtr root = build_treap(a);
        CPPUNIT_ASSERT_EQUAL(9, ImplicitTreap::range_query(root, 1, 2));

        ImplicitTreap::range_update(root, 1, 3, 2);
        // 1 6 7 4 3
        CPPUNIT_ASSERT_EQUAL(13, ImplicitTreap::range_query(root, 1, 2));
        CPPUNIT_ASSERT_EQUAL(17, ImplicitTreap::range_query(root, 1, 3));
        CPPUNIT_ASSERT_EQUAL(18, ImplicitTreap::range_query(root, 0, 3));
    }

    CPPUNIT_TEST_SUITE(ImplicitTreapTest);
    CPPUNIT_TEST(testRangeQuery);
    CPPUNIT_TEST(testRangeUpdate);
    CPPUNIT_TEST_SUITE_END();
};

class ImplicitTreap2Test:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testRangeQuery() {
        ImplicitTreap2 treap(5);
        vector<int> a = list_of(0)(1)(4)(5)(2)(3);
        treap.build(a);
        CPPUNIT_ASSERT_EQUAL(9, treap.rangeQuery(2, 3));
        CPPUNIT_ASSERT_EQUAL(11, treap.rangeQuery(2, 4));
    }

    void testRangeUpdate() {
        ImplicitTreap2 treap(5);
        vector<int> a = list_of(0)(1)(4)(5)(2)(3);
        treap.build(a);
        CPPUNIT_ASSERT_EQUAL(9, treap.rangeQuery(2, 3));

        treap.rangeUpdate(2, 4, 2);

        // 0 1 6 7 4 3
        CPPUNIT_ASSERT_EQUAL(13, treap.rangeQuery(2, 3));
        CPPUNIT_ASSERT_EQUAL(17, treap.rangeQuery(2, 4));
        CPPUNIT_ASSERT_EQUAL(18, treap.rangeQuery(1, 4));
    }

    void testGet() {
        ImplicitTreap2 treap(5);
        vector<int> a = list_of(0)(1)(4)(5)(2)(3);
        treap.build(a);

        for (int i = 1; i <= 5; i++) {
            CPPUNIT_ASSERT_EQUAL(a[i], treap[i]);
        }
    }

    void testInsert() {
        ImplicitTreap2 treap(10);
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

    CPPUNIT_TEST_SUITE(ImplicitTreap2Test);
    CPPUNIT_TEST(testRangeQuery);
    CPPUNIT_TEST(testRangeUpdate);
    CPPUNIT_TEST(testGet);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImplicitTreapTest);
CPPUNIT_TEST_SUITE_REGISTRATION(ImplicitTreap2Test);
