#include <bits/stdc++.h>

void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

struct Edge {
    int from, to;
    double cost;
    Edge() = default;
    Edge(int from, int to, double cost): from(from), to(to), cost(cost) {}
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
private:
    std::vector<int> parent;
};

int main() {
    optimize_cpp_stdio();
    int n, m;
    std::cin >> n >> m;
    auto distance = [&](const std::pair<int, int>&lhs, const std::pair<int, int>& rhs) {
        auto qrt = [&](int x) { return x * x; };
        return sqrt(qrt(lhs.first - rhs.first) + qrt(lhs.second - rhs.second));
    };
    std::vector<std::pair<int, int>> location(n);
    for (int i = 0; i < n; i++)
        std::cin >> location[i].first >> location[i].second;
    std::vector<Edge> edges;
    edges.reserve(m);
    for (int i = 0, u, v; i < m; i++) {
        std::cin >> u >> v;
        double cost = distance(location[--u], location[--v]);
        edges.emplace_back(u, v, cost);
    }
    std::sort(edges.begin(), edges.end());
    Dsu dsu(n);
    double ans = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].from, v = edges[i].to;
        if (dsu.find(u) != dsu.find(v)) dsu.unit(u, v);
        else ans += edges[i].cost;
    }
    char buf[50];
    sprintf(buf, "%.3lf", ans);
    std::cout << buf << "\n";
    return 0;
}
