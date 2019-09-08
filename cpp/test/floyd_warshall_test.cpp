#include <bits/stdc++.h>

using namespace std;

#include "graph/floyd_warshall.h"

#include <cppunit/extensions/HelperMacros.h>

class FloydWarshallTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void test() {
        vector<vector<int64_t>> g(4);
        for (int i = 0; i < 4; i++) g[i].resize(4, 1e9);
        g[0][1] = 12;
        g[1][2] = 7;
        g[2][3] = 9;
        g[3][0] = 14;
        g[0][2] = 16;
        FloydWarshall floyd(g);
        auto actual = floyd.dist_;

        vector<vector<int64_t>> expected = {
            {39, 12, 16, 25},
            {30, 42, 7, 16},
            {23, 35, 39, 9},
            {14, 26, 30, 39}
        };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                CPPUNIT_ASSERT_EQUAL(expected[i][j], actual[i][j]);
            }
        }
    }

    CPPUNIT_TEST_SUITE(FloydWarshallTest);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FloydWarshallTest);

