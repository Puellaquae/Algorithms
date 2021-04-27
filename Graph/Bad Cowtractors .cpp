#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>


void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

struct Edge {
    int from, to, cost;
    Edge() {}
    Edge(int from, int to, int cost): from(from), to(to), cost(cost) {}
    bool operator < (const Edge& other) const {
        return cost > other.cost;
    }
};

struct Dsu {
    Dsu(int n): parent(n, -1) {}
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    void unit(int u, int v) {
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

int main() {
    optimize_cpp_stdio();
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        std::cin >> edges[i].from >> edges[i].to >> edges[i].cost;
        --edges[i].from;
        --edges[i].to;
    }
    std::sort(edges.begin(), edges.end());
    Dsu dsu(n);
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].from, v = edges[i].to;
        if (dsu.find(u) != dsu.find(v)) {
            ans += edges[i].cost;
            dsu.unit(u, v);
        }
    }
    std::cout << (dsu.size(0) == n ? ans : -1) << "\n";
    return 0;
}
