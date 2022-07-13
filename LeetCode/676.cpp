#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TrieNode {
    vector<TrieNode *> next = vector<TrieNode *>(26, nullptr);
    bool end = false;
};

class MagicDictionary {

    TrieNode root;

public:
    MagicDictionary() {}

    void buildDict(vector<string> dictionary) {
        for (auto w : dictionary) {
            auto cur = &root;
            for (char c : w) {
                if (cur->next[c - 'a'] == nullptr) {
                    cur->next[c - 'a'] = new TrieNode();
                }
                cur = cur->next[c - 'a'];
            }
            cur->end = true;
        }
    }

    bool search(TrieNode *cur, string::iterator cit, const string::iterator end, bool used = false) {
        if (cur == nullptr) {
            return false;
        }
        if (cur->end && cit == end && used) {
            return true;
        }
        if (cit == end) {
            return false;
        }
        
        bool ans = false;
        for (int i = 0; i < 26; i++) {
            if (i != (*cit - 'a') && !used) {
                ans |= search(cur->next[i], next(cit), end, true);
            } else if (i == (*cit - 'a')) {
                ans |= search(cur->next[i], next(cit), end, used);
            }
            if (ans) {
                break;
            }
        }
        return ans;
    }

    bool search(string searchWord) {
        return search(&root, searchWord.begin(), searchWord.end(), false);
    }
};

int main() {
    MagicDictionary d;
    d.buildDict({"hello", "leetcode"});
    cout << d.search("hello") << endl;
    cout << d.search("hhllo") << endl;
    cout << d.search("hell") << endl;
    cout << d.search("leetcoded") << endl;
}