#include <bits/stdc++.h>

using namespace std;

#include "HeavyLightDecomposition.h"

#include <boost/assign/list_of.hpp>

#include <cppunit/extensions/HelperMacros.h>

using namespace boost::assign;

class HLDTest: public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testPrepare() {
        HeavyLightDecomposition hld(14);
        
        hld.addEdge(0, 1);
        hld.addEdge(1, 4);
        hld.addEdge(1, 5);
        hld.addEdge(5, 10);
        hld.addEdge(5, 11);
        hld.addEdge(0, 2);
        hld.addEdge(2, 6);
        hld.addEdge(0, 3);
        hld.addEdge(3, 7);
        hld.addEdge(3, 8);
        hld.addEdge(8, 12);
        hld.addEdge(12, 13);
        hld.addEdge(3, 9);

        hld.decompose();

        CPPUNIT_ASSERT(hld.Seg_size == 14);

        vector<int> result;
        for (int i =0 ; i < 13; i++) {
            result.push_back(hld.stIdx[2*i+1]);
        }
        vector<int> expected = {9, 13, 10, 12, 11, 7, 8, 1, 6, 2, 3, 4, 5};
        CPPUNIT_ASSERT(expected == result);

        expected = {0, 1, 2, 0, 4, 1, 2, 7, 0, 9, 10, 1, 0, 0};
        CPPUNIT_ASSERT(expected == hld.top);
    }

    void testUpdate() {
        HeavyLightDecomposition hld(14);
        hld.addEdge(0, 1);
        hld.addEdge(1, 4);
        hld.addEdge(1, 5);
        hld.addEdge(5, 10);
        hld.addEdge(5, 11);
        hld.addEdge(0, 2);
        hld.addEdge(2, 6);
        hld.addEdge(0, 3);
        hld.addEdge(3, 7);
        hld.addEdge(3, 8);
        hld.addEdge(8, 12);
        hld.addEdge(12, 13);
        hld.addEdge(3, 9);

        hld.decompose();

        hld.updateEdge(2, 12, 1);
        hld.updateEdge(7, 13, 2);
        hld.updateEdge(0, 10, 3);

        vector<int> result(13);
        result[0] = hld.queryEdge(0, 3);
        result[1] = hld.queryEdge(3, 8);
        result[2] = hld.queryEdge(8, 12);
        result[3] = hld.queryEdge(12, 13);
        result[4] = hld.queryEdge(3, 9);
        result[5] = hld.queryEdge(3, 7);
        result[6] = hld.queryEdge(0, 2);
        result[7] = hld.queryEdge(2, 6);
        result[8] = hld.queryEdge(0, 1);
        result[9] = hld.queryEdge(1, 5);
        result[10] = hld.queryEdge(5, 11);
        result[11] = hld.queryEdge(5, 10);
        result[12] = hld.queryEdge(1, 4);
        vector<int> expected = {1, 3, 3, 2, 0, 2, 1, 0, 3, 3, 0, 3, 0};
        CPPUNIT_ASSERT(expected ==  result);
    }

    void testRangeQueryEdge() {
        HeavyLightDecomposition hld(14);
        hld.addEdge(0, 1);
        hld.addEdge(1, 4);
        hld.addEdge(1, 5);
        hld.addEdge(5, 10);
        hld.addEdge(5, 11);
        hld.addEdge(0, 2);
        hld.addEdge(2, 6);
        hld.addEdge(0, 3);
        hld.addEdge(3, 7);
        hld.addEdge(3, 8);
        hld.addEdge(8, 12);
        hld.addEdge(12, 13);
        hld.addEdge(3, 9);

        hld.decompose();

        hld.updateEdge(2, 12, 1);
        hld.updateEdge(7, 13, 2);
        hld.updateEdge(0, 10, 3);

        CPPUNIT_ASSERT_EQUAL(9, hld.queryEdge(0, 13));
        CPPUNIT_ASSERT_EQUAL(8, hld.queryEdge(6, 12));
        CPPUNIT_ASSERT_EQUAL(13, hld.queryEdge(8, 10));
        CPPUNIT_ASSERT_EQUAL(9, hld.queryEdge(7, 5));
        CPPUNIT_ASSERT_EQUAL(0, hld.queryEdge(9, 9));
    }


    CPPUNIT_TEST_SUITE(HLDTest);
    CPPUNIT_TEST(testPrepare);
    CPPUNIT_TEST(testUpdate);
    CPPUNIT_TEST(testRangeQueryEdge);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HLDTest);
