#include "SuffixTree.cpp"

#include <boost/format.hpp>
#include <cppunit/extensions/HelperMacros.h>

class SuffixTreeTest:public CppUnit::TestFixture {
public:
    void setUp() {}
    void tearDown() {}

    void testBuild() {
        SuffixTree st;
        SuffixNode* root = st.buildSuffixTree("banana$");
        string tree = serialize(root, 0, 0);
        CPPUNIT_ASSERT(tree ==
            "0#0#0#0#0$1#0#0#1#2$2#13#1#2#4$3#13#3#4#7$"
            "3#26#3#6#7$2#26#1#6#7$1#1#0#0#7$1#13#0#2#4$"
            "2#13#2#4#7$2#26#2#6#7$1#26#0#6#7$");
    }

private:
    string serialize(SuffixNode* node, int recur, int idx) {
        string result;
        if (node) {
            result += serializeNode(node, recur, idx);
            for (int i = 0; i < SuffixNode::ALPHASIZE; i++) {
                result += serialize(node->children[i], recur+1, i);
            }
        }
        return result;
    }

    string serializeNode(SuffixNode* node, int recur, int idx) {
        string result = (boost::format{"%d#%d#%d#%d#%d$"} 
                         % recur % idx % node->depth 
                         % node->begin % node->end).str();
        return result;
    }

    CPPUNIT_TEST_SUITE(SuffixTreeTest);
    CPPUNIT_TEST(testBuild);
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SuffixTreeTest);

