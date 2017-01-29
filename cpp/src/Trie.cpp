#include <vector>

using namespace std;

// An implementation of full binary trie using vector
template <class T>
class FullBinaryTrie {
public:
    class Iterator {
    public:
        Iterator(FullBinaryTrie<T>& trie_):trie(trie_), idx(1) {}
        Iterator(const Iterator&) = default;
        ~Iterator() = default;

        T& operator *() {
            return trie.data.at(idx);
        }

        Iterator& goLeft()  {idx = 2*idx; return *this;}
        Iterator& goRight() {idx = 2*idx+1; return *this;}
        Iterator& goUp()    {idx >>= 1; return *this;}

        Iterator left() {
            return Iteartor(trie, 2*idx);
        }

        Iterator right() {
            return Iterator(trie, 2*idx+1);
        }
    private:
        Iterator(FullBinaryTrie<T>& trie_, int idx_):trie(trie_), idx(idx_) {}
        FullBinaryTrie& trie;
        int idx;
    };

    FullBinaryTrie(int level) {
        int length = (1 << level);
        data.resize(length);
    }

    FullBinaryTrie(const FullBinaryTrie&) = delete;
    ~FullBinaryTrie() = default;

    Iterator root() {
        return Iterator(*this);
    }

private:
    vector<T> data;

    friend Iterator;
    friend class FullBinaryTrieTest;
};
