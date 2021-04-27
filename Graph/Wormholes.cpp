#include <vector>
#include <iostream>

struct Edge {
    int from, to, cost;
    Edge(int from, int to, int cost): from(from), to(to), cost(cost) {}
};

void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

bool bellman_ford(int n, const std::vector<Edge>& edges) {
    std::vector<int> distance(n);
    for (int i = 0; i < n; i++) {
        bool relaxed = false;
        for (int j = 0; j < (int)edges.size(); j++) {
            const Edge& e = edges[j];
            if (distance[e.from] + e.cost < distance[e.to]) {
                distance[e.to] = distance[e.from] + e.cost;
                relaxed = true;
            }
        }
        if (not relaxed)
            return false;
    }
    return true;
}

int main() {
    optimize_cpp_stdio();
    int T;
    std::cin >> T;
    while (T--) {
        int n, m, k;
        std::cin >> n >> m >> k;
        std::vector<Edge> edges;
        for (int i = 0, u, v, w; i < m; i++) {
            std::cin >> u >> v >> w;
            edges.push_back(Edge(--u, --v, w));
            edges.push_back(Edge(v, u, w));
        }
        for (int i = 0, u, v, w; i < k; i++) {
            std::cin >> u >> v >> w;
            edges.push_back(Edge(--u, --v, -w));
        }
        std::cout << (bellman_ford(n, edges) ? "YES\n" : "NO\n");
    }
    return 0;
}
