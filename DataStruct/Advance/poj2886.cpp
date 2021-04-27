// Who Gets the Most Candies?

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define MAX_N 500016
int factorTable[MAX_N];
char names[MAX_N][64];
int cards[MAX_N];
void initFactorTable(int n) {
    memset(factorTable, 0, sizeof(factorTable));
    for (int i = 1; i < n; i++)
        for (int j = 1; i * j < n; j++)
            factorTable[i * j]++;
}

template <class T, int MAX_N_> class BinaryIndexedTree {
private:
    T bit[MAX_N_];
    int size;

public:
    BinaryIndexedTree(int size_) : size(size_) { memset(bit, 0, sizeof(bit)); }
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= (i & -i);
        }
        return s;
    }
    void add(int i, T v) {
        ++i;
        while (i <= MAX_N_) {
            bit[i] += v;
            i += (i & -i);
        }
    }
    int binaryReSearch(T id) {
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

int main() {
    int n, k;
    initFactorTable(MAX_N);
    while (~scanf("%d%d", &n, &k)) {
        BinaryIndexedTree<int, MAX_N> bit(n);
        for (int i = 0; i < n; i++) {
            scanf("%s %d", names[i], cards + i);
            bit.add(i, 1);
        }
        int maxC = -1;
        int maxS = 0;
        int nxt = k - 1;
        for (int p = 1; p <= n; p++) {
            int Fp = factorTable[p];
            if (Fp > maxS) {
                maxC = nxt;
                maxS = Fp;
            }
            bit.add(nxt, -1);
            if (p < n) {
                int mod = n - p;
                int id = bit.sum(nxt) + cards[nxt] + (cards[nxt] > 0 ? -1 : 0);
                id = (id % mod + mod) % mod;
                nxt = bit.binaryReSearch(id);
            }
        }
        printf("%s %d\n", names[maxC], maxS);
    }
}