// Segment Tree
#include <iostream>
#include <vector>
namespace Mine {
typedef unsigned int uint;
template <class T> class SegTree {
private:
    class Node {
        Node *LeftChild;
        Node *RightChild;
        T MinValue;
        T MaxValue;
        int LeftIndex;
        int RightIndex;
        bool Lazy = false;
    };
    Node *Top;
    std::vector<Node> Nodes;
    uint Update2Size(uint size) {
        uint _size = 1;
        while (_size < size) {
            _size << 1;
        }
        return _size;
    }

public:
    SegTree(uint SIZE, int Nums[]) {
        uint _size = Update2Size(SIZE);
        Nodes = new std::vector<int>(_size * 2 - 1);
        uint pos = 0;
        for (; pos < SIZE; pos++) {
            Nodes[pos].MinValue = Nodes[pos].MaxValue = Nums[pos];
        }
    }
};
} // namespace Mine

template <typename T, int N> class SegTreeInBook {
    int n;
    std::vector<T> dat;
    T (*cmp)(T, T);

public:
    SegTreeInBook(T (*cmp_)(T, T)) : cmp(cmp_) {
        n = 1;
        while (n < N) {
            n *= 2;
        }
        dat(2 * n);
        for (int i = 0; i < 2 * n - 1; i++) {
            dat[i] = INT_MAX;
        }
    }
    void update(int k, T a) {
        k += n - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = cmp(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    T query(int a, int b, int k = 0, int l = 0, int r = N) {
        if (r <= a || b <= l) {
            return dat[k];
        } else {
            T v1 = query(a, b, k * 2 + 1, 1, (l + r) / 2);
            T v2 = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return cmp(v1, v2);
        }
    }
};
/**
 * This SegTree Used in Range Frequent Query
 * T need support operator=
 * From poj3368
 * https://www.hankcs.com/program/algorithm/poj-3368-frequent-values-am.html
 * From Up to Down
 * Has Four Case In Merge
 * Default
 *    inherit LeftChild's Left & RightChild's Right
 * Left-Child's Right == Right-Child's Left
 *    Merge Left And Right
 * Left-Child's Left == Right-Child's Left
 *    Merge Left-Child And Right-Child's Left
 * Left-Child's Right == Right-Child's Right
 *    Merge Right-Child And Left-Child's Right
 * Bravo!
 * **/
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

template <typename T, int SIZE> class BIT {
    T bit[SIZE];

public:
    // sum[0,i]
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= (i & -i);
        }
        return s;
    }

    // sum[from, to)
    T sum(int from, int to) { return sum(to - 1) - sum(from - 1); }

    // bit[i] += v
    void add(int i, T v) {
        while (i <= SIZE) {
            bit[i] += v;
            i += (i & -i);
        }
    }
};

// Require BIT
template <typename T, int SIZE> class BiBIT {
    BIT<T, SIZE> bit0, bit1;

public:
    // sum[0,i]
    T sum(int i) { return bit1.sum(i) * i + bit0.sum(i); }

    // sum(from, to]
    T sum(int from, int to) { return sum(to) - sum(from); }

    //[from, to]
    void add(int from, int to, T x) {
        bit0.add(from, -x * (from - 1));
        bit1.add(from, x);
        bit0.add(to, x * to);
        bit1.add(to, -x);
    }
};

namespace _2D_BIT {
#define lowbit(x) (x & -x)

int c[N][N], n, m;

int sum(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        for (int j = y; j >= 1; j -= lowbit(j)) {
            ret += c[i][j];
        }
    }
    return ret;
}

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            c[i][j]++;
        }
    }
}
} // namespace _2D_BIT

namespace BIT1990 {
typedef long long i64;
using namespace std;
pair<int, int> cow[MAX_N];
int N;
i64 tCount[MAX_N], tDistance[MAX_N];

// a[0，i]
i64 sum(i64 *bit, int i) {
    i64 s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

// a[from, to)
i64 sum(i64 *bit, int from, int to) {
    return sum(bit, to - 1) - sum(bit, from - 1);
}

// a[i] += x
void add(i64 *bit, int i, i64 x) {
    while (i <= MAX_N) {
        bit[i] += x;
        i += i & -i;
    }
}
} // namespace BIT1990

/**
 * https://www.hankcs.com/program/algorithm/poj-2886-who-gets-the-most-candies.html
 * POJ 2886 For example:
 * Given 6 children
 *              1 1 1 1 1 1
 * with indexed 1 2 3 4 5 6
 * Then 2nd is Out
 * Origin: 1 0 1 1 1 1
 * Index:  1 X 3 4 5 6
 * Then Will Out 3-th in Rest
 * Which Means Sum start to unknown-index in Origin is 3
 * Just Find x where Sum(x) == 3 (An Inverse Function of Sum)
 * The x is the next will be out in origin index
 * In this example x is 4, so 4 will be out next
 * Très bien! Une si merveilluse idée!
 * **/
namespace BIT2886 {
template <class T, int MAX_N_> class BinaryIndexedTree {
public:
    T bit[MAX_N_];
    int size;
    BinaryIndexedTree(int size_) : size(size_) { memset(bit, 0, sizeof(bit)); }

    // sum [0,i)
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= (i & -i);
        }
        return s;
    }

    void add(int i, T v) {
        ++i; // 防止如果i是0的话，下面的循环永远不会终止
        while (i <= MAX_N_) {
            bit[i] += v;
            i += (i & -i);
        }
    }

    // 二分搜索真实下标
    int inverseSum(T id) {
        int lb = 0, ub = size;
        while (ub - lb > 1) {
            int mid = (ub + lb) >> 1;
            if (sum(mid) <= id) {
                lb = mid;
            } else {
                ub = mid;
            }
        }
        return lb;
    }
};
} // namespace BIT2886

namespace RMQ {
class RangeMinimumQuery {
    int size;
    int dat[1 << 18];
    // min of range[a,b)
    int query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l)
            return 0x3f3f3f3f;
        if (a <= l && r <= b)
            return dat[k];
        return min(query(a, b, k * 2 + 1, l, (l + r) / 2),
                   query(a, b, k * 2 + 2, (l + r) / 2, r));
    }

public:
    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        memset(dat, 0x3f, sizeof(int) * size * 2);
    }

    // set value[k] = a
    void update(int k, int a) {
        k += size - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    // min of range[a,b)
    int query(int a, int b) { return query(a, b, 0, 0, size); }

    // get value[k]
    int get(int k) { return dat[k + size]; }
}
} // namespace RMQ