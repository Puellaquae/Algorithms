// Road Construction
// Using Dijkstra
#include <iostream>
#include <vector>
#include <queue>

struct edge {
    int To, Distance, Cost;
    edge(int to, int dist, int cost) : To(to), Distance(dist), Cost(cost) {}
};

#ifndef INT_MAX
#define INT_MAX 0x7fffffff
#endif

using namespace std;

int main() {
    int N, M;
    while (cin >> N >> M && N) {//Fuck,M could be ZERO
        vector<vector<edge> > G(N);
        for (int i = 0, u, v, d, c; i < M; i++) {
            cin >> u >> v >> d >> c;
            u--;
            v--;
            G[u].emplace_back(v, d, c);
            G[v].emplace_back(u, d, c);
        }
        vector<int> D(G.size(), INT_MAX);
        D[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
        Q.emplace(0, 0);
        while (!Q.empty()) {
            int v = Q.top().second;
            int Distance = Q.top().first;
            Q.pop();
            if (D[v] != Distance) {
                continue;
            }
            for (edge e : G[v]) {
                if (D[e.To] > D[v] + e.Distance) {
                    D[e.To] = D[v] + e.Distance;
                    Q.emplace(D[e.To], e.To);
                }
            }
        }
        int ans = 0;
        for (int i = 1; i < N; i++) {
            int c = INT_MAX;
            for (edge &e : G[i]) {
                if (D[i] == D[e.To] + e.Distance) {
                    c = min(c, e.Cost);
                }
            }
            ans += c;
        }
        cout << ans << '\n';
    }
    return 0;
}