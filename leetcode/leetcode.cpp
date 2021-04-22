#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TrieNode
{
public:
    TrieNode() {
        next_.resize(26);
        is_word_ = false; 
    }
    bool is_word_ = false;
    ~TrieNode()
    {
        for (auto &node : next_)
        {
            if (node) delete node;
        }
        next_.clear();
    }

public:
    std::vector<TrieNode *> next_;
};

class Trie
{
public:
    /** Initialize your data structure here. */
    Trie() { root_ = new TrieNode(); }

    ~Trie()
    {
        if (root_) delete root_;
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        TrieNode *p = root_;
        for (auto &ch : word)
        {
            if (p->next_[ch - 'a'] == nullptr)
                p->next_[ch - 'a'] = new TrieNode();
            p = p->next_[ch - 'a'];
        }
        p->is_word_ = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        if (!root_) return false;
        TrieNode *p = root_;
        for (auto &ch : word)
        {
            p = p->next_[ch - 'a'];
            if (!p) return false;
        }
        return p->is_word_;
    }

    /** Returns if there is any word in the trie that starts with the given
     * prefix. */
    bool startsWith(string prefix)
    {
        TrieNode *p = root_;
        for (auto &ch : prefix)
        {
            p = p->next_[ch - 'a'];
            if (!p) return false;
        }
        return p;
    }

private:
    TrieNode *root_;
};

int main()
{   
    Trie trie;
    trie.insert("lsp");
    trie.insert("hg");
    trie.insert("psg");

    bool s = trie.search("hello");
     s = trie.search("psg");
    return 0;
}