#include "data_structures/implicit_treap.h"

#include <iostream>
#include <vector>

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

CPPUNIT_TEST_SUITE_REGISTRATION(ImplicitTreapTest);
