#ifndef SEGMENTTREEMINTEST_H
#define SEGMENTTREEMINTEST_H

#include <cppunit/extensions/HelperMacros.h>

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

#endif
