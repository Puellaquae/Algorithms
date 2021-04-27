#include <queue>
#include <vector>
#include <utility>
#include <iostream>


void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

const int INF = 0x3f3f3f3f;

std::vector<int> dijkstra(int s, const std::vector<std::vector<std::pair<int, int>>>& G) {
    std::vector<int> distance(G.size(), INF);
    std::priority_queue<std::pair<int, int>> q;
    q.push(std::make_pair(distance[s] = 0, s));
    while (!q.empty()) {
        int from = q.top().second;
        int current = -q.top().first;
        q.pop();
        if (current != distance[from])
            continue;
        for (int i = 0; i < (int)G[from].size(); i++) {
            const std::pair<int, int>& e = G[from][i];
            if (distance[from] + e.second < distance[e.first]) {
                distance[e.first] = distance[from] + e.second;
                q.push(std::make_pair(-distance[e.first], e.first));
            }
        }
    }
    return distance;
}

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    --s;
    std::vector<std::vector<std::pair<int, int>>> G1(n);
    std::vector<std::vector<std::pair<int, int>>> G2(n);
    for (int i = 0, u, v, w; i < m; i++) {
        std::cin >> u >> v >> w;
        G1[--u].push_back(std::make_pair(--v, w));
        G2[v].push_back(std::make_pair(u, w));
    }
    std::vector<int> forward = dijkstra(s, G1);
    std::vector<int> reverse = dijkstra(s, G2);
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = std::max(ans, forward[i] + reverse[i]);
    std::cout << ans << "\n";
    return 0;
}
