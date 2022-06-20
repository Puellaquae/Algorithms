#include <iostream>
#include <set>
using namespace std;

class RangeModule {
    struct Node {
        int l, r;
        mutable int v;
        inline bool operator<(const Node &o) const { return l < o.l; }
    };

    set<Node> odt;

    auto split(int x) {
        auto it = odt.upper_bound(Node {x, 0, 0});
        if (it != odt.end() && it->l == x) {
            return it;
        }
        --it;
        int l = it->l;
        int r = it->r;
        int v = it->v;
        odt.erase(it);
        odt.insert(Node {l, x - 1, v});
        return odt.insert(Node {x, r, v}).first;
    }

    void assign(int left, int right, int val) {
        auto itr = split(right + 1);
        auto itl = split(left);
        odt.erase(itl, itr);
        odt.insert(Node{left, right, val});
    }

public:
    RangeModule() {
        odt.insert(Node {1, 1000000007, 0});
    }

    void addRange(int left, int right) {
        assign(left, right - 1, 1);
    }

    bool queryRange(int left, int right) {
        auto itr = split(right);
        auto itl = split(left);
        for (; itl != itr; ++itl) {
            if (itl->v != 1) {
                return false;
            }
        }
        return true;
    }

    void removeRange(int left, int right) {
        assign(left, right - 1, 0);
    }
};

int main() {
    RangeModule r;
    r.addRange(10, 20);
    r.removeRange(14, 16);
    cout << r.queryRange(10, 14) << endl;
    cout << r.queryRange(13, 15) << endl;
    cout << r.queryRange(16, 17) << endl;
}