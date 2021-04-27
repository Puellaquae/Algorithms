// Save your cats
// Using Kruskal-Kai, Count the Cost of Deleted Edge

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

struct Dsu {
    Dsu(int n) : parent(n, -1) {}
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    bool same(int a, int b) { return find(a) == find(b); }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (parent[u] < parent[v])
            std::swap(u, v);
        parent[v] += parent[u];
        parent[u] = v;
    }
    int size(int x) { return -parent[find(x)]; }

private:
    std::vector<int> parent;
};
// Page 107
struct edge {
    int u, v;
    double cost;
};

bool comp(const edge &e1, const edge &e2) { return e1.cost < e2.cost; }

bool compKai(const edge &e1, const edge &e2) { return e1.cost > e2.cost; }

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<edge> Es(M);
    vector<int[2]> Pos(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> Pos[i][0] >> Pos[i][1];
    }
    for (int i = 0; i < M; i++) {
        int p, q;
        cin >> p >> q;
        Es[i].u = --p;
        Es[i].v = --q;
        int dx = Pos[p][0] - Pos[q][0];
        int dy = Pos[p][1] - Pos[q][1];
        Es[i].cost = sqrt(dx * dx + dy * dy);
    }
    sort(Es.begin(), Es.end(), compKai);
    Dsu d(N);
    double res = 0.0;
    for (int i = 0; i < M; i++) {
        edge e = Es[i];
        if (!d.same(e.u, e.v)) {
            d.unite(e.u, e.v);
        } else {
            res += e.cost;
        }
    }
    printf("%.3lf\n",res);
    return 0;
}