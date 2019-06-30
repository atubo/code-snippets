#include <bits/stdc++.h>

using namespace std;

#include "data_structures/sbt.h"

#include <cppunit/extensions/HelperMacros.h>

class SbtTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        Sbt sbt(5);
        sbt.insert(0);
        sbt.insert(3);
        sbt.insert(5);
        CPPUNIT_ASSERT_EQUAL(2, sbt.rank(4));
        sbt.insert(1);
        CPPUNIT_ASSERT_EQUAL(3, sbt.rank(4));
        sbt.insert(2);
        CPPUNIT_ASSERT_EQUAL(4, sbt.rank(4));
        CPPUNIT_ASSERT_EQUAL(0, sbt.rank(0));
    }

    void testDelete() {
        Sbt sbt(5);
        for (int i = 0; i < 5; i++) sbt.insert(i);
        for (int i = 0; i < 5; i++) {
            CPPUNIT_ASSERT_EQUAL(i, sbt.rank(i));
        }
        sbt.del(2);
        CPPUNIT_ASSERT_EQUAL(0, sbt.rank(0));
        CPPUNIT_ASSERT_EQUAL(1, sbt.rank(1));
        CPPUNIT_ASSERT_EQUAL(2, sbt.rank(2));
        CPPUNIT_ASSERT_EQUAL(2, sbt.rank(3));
        CPPUNIT_ASSERT_EQUAL(3, sbt.rank(4));
    }

    void testDuplicates() {
        Sbt sbt(8);
        sbt.insert(0); sbt.insert(0);
        sbt.insert(1); sbt.insert(1); sbt.insert(1);
        sbt.insert(2);
        sbt.insert(3); sbt.insert(3);

        vector<int> expected = {0, 2, 5, 6, 8};
        for (int i = 0; i < 5; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], sbt.rank(i));
        }
    }

    void testFindByOrder() {
        Sbt sbt(5);
        vector<int> elems = {0, 2, 4, 5, 6};
        for (int i = 0; i < 5; i++) sbt.insert(elems[i]);
        for (int i = 0; i < 5; i++) {
            CPPUNIT_ASSERT_EQUAL(elems[i], sbt.findByOrder(i));
        }
    }

    void testPred() {
        Sbt sbt(5);
        vector<int> elems = {0, 2, 4, 5, 6};
        for (int i = 0; i < 5; i++) sbt.insert(elems[i]);
        vector<int> expected = {INT_MIN, 0, 0, 2, 2, 4, 5, 6};
        for (int i = 0; i < 8; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], sbt.pred(i));
        }
    }

    void testSucc() {
        Sbt sbt(5);
        vector<int> elems = {1, 3, 4, 6, 7};
        for (int i = 0; i < 5; i++) sbt.insert(elems[i]);
        vector<int> expected = {1, 3, 3, 4, 6, 6, 7, INT_MAX};
        for (int i = 0; i < 8; i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], sbt.succ(i));
        }
    }


    CPPUNIT_TEST_SUITE(SbtTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST(testDelete);
    CPPUNIT_TEST(testDuplicates);
    CPPUNIT_TEST(testFindByOrder);
    CPPUNIT_TEST(testPred);
    CPPUNIT_TEST(testSucc);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SbtTest);
