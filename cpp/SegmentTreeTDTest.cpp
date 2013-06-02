#include "SegmentTreeTDTest.h"
#include "SegmentTreeTD.cpp"

CPPUNIT_TEST_SUITE_REGISTRATION(SegmentTreeTDTest);

const ll MAXINT = numeric_limits<ll>::max();

struct Node {
	Node(): delta(0), val(MAXINT) {}
    void update(const Node& left, const Node& right) {
        val   = min(left.delta  + left.val,
                    right.delta + right.val);
    }
	ll delta;
	ll val;
};

struct Updator {
    Updator(ll delta_): delta(delta_) {}
    void updateNode(Node& node) const {
        node.delta += delta;
    }
    ll delta;
};

struct Query {
    Query(): delta(0) {}

    static ll nullValue() {
        return MAXINT;
    }

    void update(const Node& node) {
        delta += node.delta;
    }

    ll getValue(const Node& node) const {
        return node.val + delta;
    }

    ll combineValues(ll p1, ll p2) const {
        return min(p1, p2);
    }

    ll delta;
};

void SegmentTreeTDTest::test1()
{
    //int64_t a[] = {1, 2, 3, 4};
    Node a[4];
    for (int i = 0; i < 4; i++) {
        a[i].val = i+1;
    }
    SegmentTreeTD<Node> tree(4, a);
    tree.update(3, 3, Updator(-1));
    tree.update(0, 0, Updator(-1));
    int x = tree.query(0, 0, Query());
    CPPUNIT_ASSERT_EQUAL(0, x);

    x = tree.query(3, 3, Query());
    CPPUNIT_ASSERT_EQUAL(3, x);

    x = tree.query(0, 1, Query());
    CPPUNIT_ASSERT_EQUAL(0, x);

    x = tree.query(2, 3, Query());
    CPPUNIT_ASSERT_EQUAL(3, x);
}

void SegmentTreeTDTest::test2()
{
    //int64_t a[3] = {0};
    Node a[3];
    for (int i = 0; i < 3; i++) {
        a[i].val = 0;
    }
    SegmentTreeTD<Node> tree(3, a);
    tree.update(0, 0, Updator(-1));
    tree.update(0, 0, Updator(1));
    for (int i = 0; i < 3; i++) {
        int x = tree.query(i, i, Query());
        CPPUNIT_ASSERT_EQUAL(0, x);
    }
}

void SegmentTreeTDTest::test3()
{
    //int64_t a[3] = {-2, -2, -2};
    Node a[3];
    for (int i = 0; i < 3; i++) {
        a[i].val = -2;
    }
    SegmentTreeTD<Node> tree(3, a);
    tree.update(0, 2, Updator(2));
    tree.update(2, 2, Updator(-1));
    int x = tree.query(0, 2, Query());
    CPPUNIT_ASSERT_EQUAL(-1, x);
}
