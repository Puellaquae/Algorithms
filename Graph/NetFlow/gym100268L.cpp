// Wi-fi Towers

/************/
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
        std::priority_queue<pii, std::vector<pii>,
                            std::greater<pii> >
            q;
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
                pii y(dist[u] + e.cost + H[u] - H[v],
                      v);
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
/************/
#include <cmath>
#include <cstdio>
#define sqr(x) ((x) * (x))
struct Tower {
    int x, y, r, s;
} Towers[505];
int main() {
    int N;
    scanf("%d", &N);
    mcmf.init(N + 2);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d%d", &Towers[i].x, &Towers[i].y,
              &Towers[i].r, &Towers[i].s);
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (Towers[i].s < 0) {
            mcmf.addEdge(N, i, -Towers[i].s, 0);
        } else {
            ans += Towers[i].s;
            mcmf.addEdge(i, N + 1, Towers[i].s, 0);
        }
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            if (sqr(Towers[i].x - Towers[j].x) +
                    sqr(Towers[i].y - Towers[j].y) <=
                sqr(Towers[i].r)) {
                mcmf.addEdge(j, i, INF, 0);
            }
        }
    }
    mcmf.solve(N, N + 1);
    ans -= mcmf.flow;
    printf("%d\n", ans);
}