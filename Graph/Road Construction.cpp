#include <bits/stdc++.h>

void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

struct Edge {
    int to, dist, cost;
    Edge(int to, int dist, int cost): to(to), dist(dist), cost(cost) {}
};

int main() {
    optimize_cpp_stdio();
    int n, m;
    while (std::cin >> n >> m && n) {
        std::vector<std::vector<Edge>> G(n);
        for (int i = 0, u, v, w, x; i < m; i++) {
            std::cin >> u >> v >> w >> x;
            G[--u].emplace_back(--v, w, x);
            G[v].emplace_back(u, w, x);
        }
        std::vector<int> distance(n, INT_MAX);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
        q.push(std::make_pair(distance[0] = 0, 0));
        while (!q.empty()) {
            int from = q.top().second;
            int current = q.top().first;
            q.pop();
            if (current != distance[from])
                continue;
            for (Edge& e : G[from]) {
                if (distance[from] + e.dist < distance[e.to]) {
                    distance[e.to] = distance[from] + e.dist;
                    q.emplace(distance[e.to], e.to);
                }
            }
        }
        int ans = 0;
        for (int from = 1; from < n; from++) {
            int cost = INT_MAX;
            for (Edge& e : G[from]) {
                if (distance[from] == distance[e.to] + e.dist)
                    cost = std::min(cost, e.cost);
            }
            ans += cost;
        }
        std::cout << ans << "\n";
    }
    return 0;
}