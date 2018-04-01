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
            result.push_back(hld.num[2*i+1]);
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

        hld.update(2, 12, 1);
        hld.update(7, 13, 2);
        hld.update(0, 10, 3);

        vector<int> result(13);
        for (int i = 0; i < 13; i++) {
            result[i] = hld.st.query(i+1, i+1);
        }
        vector<int> expected = {1, 3, 3, 2, 0, 2, 1, 0, 3, 3, 0, 3, 0};
        CPPUNIT_ASSERT(expected ==  result);
    }

    CPPUNIT_TEST_SUITE(HLDTest);
    CPPUNIT_TEST(testPrepare);
    CPPUNIT_TEST(testUpdate);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HLDTest);
