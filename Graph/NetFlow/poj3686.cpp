// The Windy's

#include <cstdio>
/************************/
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int MAXN = 100005;
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

    void solve(int S, int T) {
        this->s = S, this->t = T;
        flow = cost = 0;
        std::fill(H, H + n + 1, 0);
        while (dijkstra())
            ;
    }

    void init(int N) {
        this->n = N;
        for (int i = 0; i <= n; ++i)
            G[i].clear();
    }

    void addEdge(int u, int v, int cap, int _cost) {
        G[u].push_back({v, cap, _cost, SZ(G[v])});
        G[v].push_back({u, 0, -_cost, SZ(G[u]) - 1});
    }

} mcmf;
/************************/
int Z[55][55];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &Z[i][j]);
        int S = 0, T = m * n + n + 1;
        mcmf.init(T);
        for (int i = 1; i <= n; i++)
            mcmf.addEdge(S, i, 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                mcmf.addEdge(n + (i - 1) * m + j, T, 1, 0);
                for (int w = 1; w <= n; w++) {
                    mcmf.addEdge(w, n + (i - 1) * m + j, 1, i * Z[w][j]);
                }
            }
        }
        mcmf.solve(S, T);
        printf("%.6f\n", (double)mcmf.cost / n);
    }
    return 0;
}