// Frequent values

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
template <typename T> class SegTree {
private:
    int n;
    vector<int> length, left, right;
    vector<T> src;
    void init(int p, int l, int r) {
        if (l + 1 == r) {
            length[p] = right[p] = left[p] = 1;
            return;
        }
        int pl = p * 2 + 1, pr = p * 2 + 2, mid = (l + r) / 2;
        init(pl, l, mid);
        init(pr, mid, r);
        length[p] = max(length[pl], length[pr]);
        left[p] = left[pl];
        right[p] = right[pr];
        if (src[mid - 1] == src[mid]) {
            length[p] = max(length[p], right[pl] + left[pr]);
        }
        if (src[l] == src[mid]) {
            left[p] += left[pr];
        }
        if (src[mid - 1] == src[r - 1]) {
            right[p] += right[pl];
        }
    }

public:
    struct Result {
        int length, l, r;
        Result(int len_ = 0, int l_ = 0, int r_ = 0)
            : length(len_), l(l_), r(r_) {}
        operator int() { return max(length, max(l, r)); }
    };
    Result Query(int a, int b, int p, int l, int r) {
        int pl = p * 2 + 1, pr = p * 2 + 2, mid = (l + r) / 2;
        if (b <= l || r <= a) {
            return Result();
        } else if (a <= l && r <= b) {
            return Result(length[p], left[p], right[p]);
        } else {
            Result child_l = Query(a, b, pl, l, mid);
            Result child_r = Query(a, b, pr, mid, r);
            Result result(max(child_l.length, child_r.length), child_l.l,
                          child_r.r);
            if (src[mid - 1] == src[mid]) {
                result.length = max(result.length, child_l.r + child_r.l);
            }
            if (src[l] == src[mid]) {
                result.l += child_r.l;
            }
            if (src[mid - 1] == src[r - 1]) {
                result.r += child_l.r;
            }
            return result;
        }
    }
    SegTree(int n_, vector<T> &src_)
        : n(n_), length(n_ * 3 + 1), left(n_ * 3 + 1), right(n_ * 3 + 1),
          src(src_) {
        init(0, 0, n_);
    }
    Result Query(int a, int b) { return Query(a, b, 0, 0, n); }
};

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) {
            break;
        }
        vector<int> A(n);
        int q;
        scanf("%d", &q);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        SegTree<int> tree(n, A);
        for (int i = 0; i < q; ++i) {
            int l, r;
            scanf("%d%d", &l, &r);
            l--;
            printf("%d\n", tree.Query(l, r));
        }
    }
    return 0;
}
