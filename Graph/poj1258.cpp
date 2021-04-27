// Agri-Net
// Using Kruskal, a algorithm of Minimum Spanning Tree(MST)
// Like POJ3723 Conscription
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

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

using namespace std;

int kruskal(int V, vector<edge> &es) {
    sort(es.begin(), es.end(), comp);
    init(V);
    int res = 0;
    for (int i = 0; i < es.size(); i++) {
        edge e = es[i];
        if (!same(e.u, e.v)) {
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}

int main() {
    int T;
    while (~scanf("%d", &T)) {
        vector<edge> Es;
        for (int i = 0; i < T; i++) {
            for (int j = 0; j < T; j++) {
                int c;
                scanf("%d", &c);
                if (i < j) {
                    Es.push_back({i, j, c});
                }
            }
        }
        printf("%d\n", kruskal(T, Es));
    }
}