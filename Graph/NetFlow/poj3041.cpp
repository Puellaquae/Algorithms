// Asteroids
// Using MCMF_Dijkstra

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>

const int MAXN = 20000;
const int INF = 0x7fffffff;
#define SZ(v) (int)v.size()

struct MCMF {
    struct Edge {
        int v, cap, cost, rev;
    };

    int flow, cost, s, t, n;
    int dist[MAXN], H[MAXN], pv[MAXN], pe[MAXN];
    std::vector<Edge> G[MAXN];

    bool dijkstra() {
        typedef std::pair<int, int> pii;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
        std::fill(dist, dist + n + 1, INF);
        dist[s] = 0;
        q.push({0, s});
        while (!q.empty()) {
            pii x = q.top();
            q.pop();
            int &u = x.second;
            if (dist[u] < x.first)
                continue;
            for (int i = 0; i < SZ(G[u]); ++i) {
                Edge &e = G[u][i];
                int &v = e.v;
                pii y(dist[u] + e.cost + H[u] - H[v], v);
                if (e.cap > 0 && dist[v] > y.first) {
                    dist[v] = y.first;
                    pe[v] = i, pv[v] = u;
                    q.push(y);
                }
            }
        }

        if (dist[t] == INF)
            return false;
        for (int i = 0; i <= n; ++i)
            H[i] += dist[i];

        int f = INF;
        for (int v = t; v != s; v = pv[v])
            f = std::min(f, G[pv[v]][pe[v]].cap);

        flow += f;
        cost += f * H[t];

        for (int v = t; v != s; v = pv[v]) {
            Edge &e = G[pv[v]][pe[v]];
            e.cap -= f;
            G[v][e.rev].cap += f;
        }

        return true;
    }

    int solve(int s, int t) {
        this->s = s, this->t = t;
        flow = cost = 0;
        std::fill(H, H + n + 1, 0);
        while (dijkstra())
            ;
        return flow;
    }

    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; ++i)
            G[i].clear();
    }

    void addEdge(int u, int v, int cap, int _cost) {
        G[u].push_back({v, cap, cost, SZ(G[v])});
        G[v].push_back({u, 0, -cost, SZ(G[u]) - 1});
    }

} mcmf;

int main() {
    int n, m, s, t;
    scanf("%d%d", &n, &m);
    s = n + n + 1, t = n + n + 2;
    mcmf.init(n + n + 2);
    for (int i = 0, x, y; i < m; ++i) {
        scanf("%d%d", &x, &y);
        mcmf.addEdge(x, y + n, 1, 0);
    }
    for (int i = 1; i <= n; ++i) {
        mcmf.addEdge(s, i, 1, 0);
        mcmf.addEdge(i + n, t, 1, 0);
    }
    printf("%d\n", mcmf.solve(s, t));
    return 0;
}