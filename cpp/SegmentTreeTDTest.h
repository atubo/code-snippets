#ifndef SEGMENTTREETDTEST_H
#define SEGMENTTREETDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class SegmentTreeTDTest:public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SegmentTreeTDTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {}
    void tearDown() {}
    void test1();
};

#endif
