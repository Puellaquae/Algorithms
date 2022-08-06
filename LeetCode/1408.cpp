#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Trie {
    vector<Trie *> next = vector<Trie *>(26, nullptr);
    bool insert(const string &str, int start) {
        Trie *cur = this;
        bool sub = true;

        for (; start < str.size(); start++) {
            char ch = str[start];
            if (cur->next[ch - 'a'] != nullptr) {
                cur = cur->next[ch - 'a'];
            } else {
                sub = false;
                cur->next[ch - 'a'] = new Trie();
                cur = cur->next[ch - 'a'];
            }
        }
        return sub;
    }
};

class Solution {
public:
    vector<string> stringMatching(vector<string> &words) {
        sort(words.begin(), words.end(), [](const string &a, const string &b) {
            return a.size() > b.size();
        });
        Trie trie;
        vector<string> ans;
        for (const auto &str : words) {
            if (trie.insert(str, 0)) {
                ans.push_back(str);
            }
            for (int i = 1; i < str.size(); i++) {
                trie.insert(str, i);
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<string> a{"leetcoder", "leetcode", "od", "hamlet", "am"};
    for (auto &w : s.stringMatching(a)) {
        cout << w << ", ";
    }
    cout << "\n";
}
