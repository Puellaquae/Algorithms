// Conscription
// Using
// Union-Find Set
// Kruskal, a algorithm of Minimum Spanning Tree(MST)

#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 2e5 + 10;
const int MAX_R = 5e5 + 10;
const int MAX_E = MAX_R;
// Page 87
int par[MAX_N];
int rank[MAX_N];

void init(int n) {
    for (int i = 0; i < n; i++) {
        par[i] = i;
        ::rank[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) {
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return;
    }
    if (::rank[x] < ::rank[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (::rank[x] == ::rank[y]) {
            ::rank[x]++;
        }
    }
}

bool same(int x, int y) { return find(x) == find(y); }
// Page 107
struct edge {
    int u, v, cost;
};

bool comp(const edge &e1, const edge &e2) { return e1.cost < e2.cost; }

edge es[MAX_E];
int V, E;

using namespace std;

int kruskal() {
    sort(es, es + E, comp);
    init(V);
    int res = 0;
    for (int i = 0; i < E; i++) {
        edge e = es[i];
        if (!same(e.u, e.v)) {
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}

int N, M, R;
int x[MAX_R], y[MAX_R], d[MAX_R];
void solve() {
    V = N + M;
    E = R;
    for (int i = 0; i < R; i++) {
        es[i] = (edge){x[i], N + y[i], -d[i]};
    }
    printf("%d\n", (10000 * (N + M) + kruskal()));
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &N, &M, &R);
        for (int i = 0; i < R; i++) {
            scanf("%d%d%d", x + i, y + i, d + i);
        }
        solve();
    }
}