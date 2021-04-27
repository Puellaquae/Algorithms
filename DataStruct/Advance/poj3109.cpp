// Inner Vertices

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define MAX_N 100000 + 16
typedef long long i64;

int N, X[MAX_N], Y[MAX_N];
vector<int> line[MAX_N];
bool visited[MAX_N];

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

int compress(int *p) {
    vector<int> ps(N);
    for (int i = 0; i < N; i++) {
        ps[i] = p[i];
    }
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    for (int i = 0; i < N; i++) {
        p[i] = 1 + lower_bound(ps.begin(), ps.end(), p[i]) - ps.begin();
    }
    return ps.size();
}

int main() {
    BiBIT<i64, MAX_N> bibit;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", X + i, Y + i);
    }
    int w = compress(X);
    int h = compress(Y);
    for (int i = 0; i < N; ++i) {
        line[Y[i]].push_back(X[i]);
    }
    i64 result = N;
    for (int y = 1; y <= h; y++) {
        vector<int> &xs = line[y];
        sort(xs.begin(), xs.end());
        for (vector<int>::iterator i = xs.begin(); i != xs.end(); i++) {
            int x = *i;
            i64 s = bibit.sum(x - 1, x);
            if (visited[x]) {
                result += s;
            } else {
                visited[x] = true;
            }
            bibit.add(x, x, -s);
            if (i + 1 != xs.end()) {
                if (x + 1 < *(i + 1) - 1) {
                    bibit.add(x + 1, *(i + 1) - 1, 1);
                } else if (x + 1 == *(i + 1) - 1) {
                    bibit.add(x + 1, x + 1, 1);
                }
            }
        }
    }
    printf("%lld\n", result);
    return 0;
}