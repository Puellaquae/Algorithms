// Kaka's Matrix Travels

/*********************/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int MAXN = 100000;
#ifndef INT_MAX
#    define INT_MAX 0x7fffffff
#endif
const int INF = INT_MAX;
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

    void solve(int _s, int _t) {
        this->s = _s, this->t = _t;
        flow = cost = 0;
        std::fill(H, H + n + 1, 0);
        while (dijkstra())
            ;
    }

    void init(int _n) {
        this->n = _n;
        for (int i = 0; i <= n; ++i)
            G[i].clear();
    }

    void addEdge(int u, int v, int cap, int _cost) {
        G[u].push_back({v, cap, _cost, SZ(G[v])});
        G[v].push_back({u, 0, -_cost, SZ(G[u]) - 1});
    }

} mcmf;

/*********************/
#define IND(y, x) (2 * ((y)*N + (x)) + 1)
#include <cstdio>
int mat[55][55];
int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    mcmf.init(2 * N * N + 1);
    for (int y = 0, s; y < N; y++) {
        for (int x = 0; x < N; x++) {
            scanf("%d", &s);
            mcmf.addEdge(IND(y, x), IND(y, x) + 1, 1, -s);
            mcmf.addEdge(IND(y, x), IND(y, x) + 1, K, 0);
            if (y + 1 < N) {
                mcmf.addEdge(IND(y, x) + 1, IND(y + 1, x), K, 0);
            }
            if (x + 1 < N) {
                mcmf.addEdge(IND(y, x) + 1, IND(y, x + 1), K, 0);
            }
        }
    }
    mcmf.addEdge(0, 1, K, 0);
    mcmf.solve(0, 2 * N * N);
    printf("%d\n", -mcmf.cost);
}