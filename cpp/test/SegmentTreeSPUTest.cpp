#include <bits/stdc++.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace std;

#include "SegmentTreeSPU.h"

class SegmentTreeSPUTest:public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SegmentTreeSPUTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {}
    void tearDown() {}
    void test1();
};


CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeSPUTest);

void SegmentTreeSPUTest::test1()
{
    SegmentTreeSPU tree(4);
    tree.update(0, 4);
    tree.update(1, 2);
    tree.update(2, 3);
    tree.update(3, 1);

    CPPUNIT_ASSERT_EQUAL(10, tree.query(0, 3));
    CPPUNIT_ASSERT_EQUAL(9, tree.query(0, 2));
    CPPUNIT_ASSERT_EQUAL(6, tree.query(1, 3));
}
