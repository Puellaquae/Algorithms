// Bad Cowtractors
// Using Kruskal-Kai, Maximum Spanning Tree
// Like POJ1258 Agri-Net
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

struct Dsu {
    Dsu(int n): parent(n, -1) {}
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    bool same(int a,int b){return find(a)==find(b);}
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (parent[u] < parent[v])
            std::swap(u, v);
        parent[v] += parent[u];
        parent[u] = v;
    }
    int size(int x) {
        return -parent[find(x)];
    }
private:
    std::vector<int> parent;
};
// Page 107
struct edge {
    int u, v, cost;
};

bool comp(const edge &e1, const edge &e2) { return e1.cost < e2.cost; }

bool compKai(const edge &e1, const edge &e2) { return e1.cost > e2.cost; }

using namespace std;

int kruskal(int V, vector<edge> &es,int &s) {
    sort(es.begin(), es.end(), compKai);
    Dsu d(V);
    int res = 0;
    for (int i = 0; i < es.size(); i++) {
        edge e = es[i];
        if (!d.same(e.u, e.v)) {
            d.unite(e.u, e.v);
            res += e.cost;
        }
    }
    s=d.size(0);
    return res;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<edge> Es(M);
    for (int i = 0; i < M; i++) {
        cin >> Es[i].u >> Es[i].v >> Es[i].cost;
        Es[i].u--;
        Es[i].v--;
    }
    int S;
    int ans = kruskal(N, Es,S);
    cout << (S == N ? ans : -1) << endl;
}