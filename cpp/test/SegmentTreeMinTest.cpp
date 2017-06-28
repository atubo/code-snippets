#include <bits/stdc++.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace std;

#include "SegmentTreeMin.h"

class SegmentTreeMinTest:public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SegmentTreeMinTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {}
    void tearDown() {}
    void test1();
    void test2();
};


CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeMinTest);

void SegmentTreeMinTest::test1()
{
    SegmentTreeMin tree(4, 1000, [](int i, int j){return min(i, j);});
    tree.update(0, 4);
    tree.update(1, 2);
    tree.update(2, 3);
    tree.update(3, 1);

    CPPUNIT_ASSERT_EQUAL(1, tree.query(0, 3));
    CPPUNIT_ASSERT_EQUAL(2, tree.query(0, 2));
    CPPUNIT_ASSERT_EQUAL(1, tree.query(1, 3));
}

void SegmentTreeMinTest::test2()
{
    SegmentTreeMin tree(15, 1000, [](int i, int j){return i|j;});
    for (int i = 0; i < 15; i++) {
        tree.update(i, i+1);
    }

    CPPUNIT_ASSERT_EQUAL(15, tree.query(5, 9));
}
