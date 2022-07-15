#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Trie {
    map<pair<char, char>, Trie *> next = map<pair<char, char>, Trie *>();
    int idx = -1;
    template<class It, class RevIt>
    Trie *go(int idx, It a, It ae, RevIt b, RevIt be) {
        auto cur = this;
        for (auto cb = b; cb != be; ++cb) {
            auto key = make_pair('#', *cb);
            if (cur->next.count(key) == 0) {
                cur->next[key] = new Trie();
            }
            cur = cur->next[key];
            cur->idx = idx;
        }
        cur = this;
        for (auto ca = a; ca != ae; ++ca) {
            auto key = make_pair(*ca, '#');
            if (cur->next.count(key) == 0) {
                cur->next[key] = new Trie();
            }
            cur = cur->next[key];
            cur->idx = idx;
        }
        auto key = make_pair(*a, *b);
        if (next.count(key) == 0) {
            next[key] = new Trie{};
            
        }
        cur = next[key];
        cur->idx = idx;
        return cur;
    }
    Trie *to(char a, char b) {
        auto key = make_pair(a, b);
        if (next.count(key) == 0) {
            return nullptr;
        }
        return next[key];
    }
};

class WordFilter {
    Trie root;

public:
    WordFilter(const vector<string> &words) {
        int idx = 0;
        for (auto &word : words) {
            auto b = word.begin();
            auto r = word.rbegin();
            auto cur = &root;
            while (b != word.end() && r != word.rend()) {
                cur = cur->go(idx, b++, word.end(), r++, word.rend());
            }
            idx++;
        }
    }

    int f(string pref, string suff) {
        auto a = pref.begin();
        auto b = suff.rbegin();
        auto cur = &root;
        while (a != pref.end() || b != suff.rend()) {
            cur = cur->to(a == pref.end() ? '#' : *a++,
                          b == suff.rend() ? '#' : *b++);
            if (cur == nullptr) {
                return -1;
            }
        }
        return cur->idx;
    }
};

int main() {
    WordFilter w({"apple"});
    cout << w.f("a", "e") << endl;
    cout << w.f("ap", "e") << endl;
    cout << w.f("ap", "ple") << endl;
    cout << w.f("apl", "ple") << endl;
}