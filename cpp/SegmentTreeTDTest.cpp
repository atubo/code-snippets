#include "SegmentTreeTDTest.h"
#include "SegmentTreeTD.cpp"

#include <cassert>

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeTDTest);

typedef int64_t ll;

const ll MAXINT = numeric_limits<ll>::max();

struct Node {
    typedef ll QVType;  // query return value type
    typedef ll QAType;  // query argument type
    typedef ll UVType;  // update value type

    Node(): delta(0), val(MAXINT) {}
    void update(const Node& left, const Node& right) {
        val   = min(left.delta  + left.val,
                    right.delta + right.val);
    }
    ll delta;
    ll val;

    struct Updator {
        Updator(UVType delta_): delta(delta_) {}
        void updateNode(Node& node) const {
            node.delta += delta;
        }
        UVType delta;
    };

    struct Query {
        Query(const QAType& q): delta(0) {
            assert(q == 0);
        }

        static QVType nullValue() {
            return MAXINT;
        }

        void update(const Node& node) {
            delta += node.delta;
        }

        QVType getValue(const Node& node) const {
            return node.val + delta;
        }

        QVType combineValues(QVType p1, QVType p2) const {
            return min(p1, p2);
        }

        ll delta;
    };
};



void SegmentTreeTDTest::test1()
{
    // a[] = {1, 2, 3, 4}
    Node a[4];
    for (int i = 0; i < 4; i++) {
        a[i].val = i+1;
    }
    SegmentTreeTD<Node> tree(4, a);
    tree.update(3, 3, -1);
    tree.update(0, 0, -1);
    int x = tree.query(0, 0, 0);
    CPPUNIT_ASSERT_EQUAL(0, x);

    x = tree.query(3, 3, 0);
    CPPUNIT_ASSERT_EQUAL(3, x);

    x = tree.query(0, 1, 0);
    CPPUNIT_ASSERT_EQUAL(0, x);

    x = tree.query(2, 3, 0);
    CPPUNIT_ASSERT_EQUAL(3, x);
}

void SegmentTreeTDTest::test2()
{
    // a[3] = {0, 0, 0}
    Node a[3];
    for (int i = 0; i < 3; i++) {
        a[i].val = 0;
    }
    SegmentTreeTD<Node> tree(3, a);
    tree.update(0, 0, -1);
    tree.update(0, 0, 1);
    for (int i = 0; i < 3; i++) {
        int x = tree.query(i, i, 0);
        CPPUNIT_ASSERT_EQUAL(0, x);
    }
}

void SegmentTreeTDTest::test3()
{
    // a[3] = {-2, -2, -2}
    Node a[3];
    for (int i = 0; i < 3; i++) {
        a[i].val = -2;
    }
    SegmentTreeTD<Node> tree(3, a);
    tree.update(0, 2, 2);
    tree.update(2, 2, -1);
    int x = tree.query(0, 2, 0);
    CPPUNIT_ASSERT_EQUAL(-1, x);
}
