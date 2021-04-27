// Intervals

/********************/
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int MAXN = 100000;
#ifndef INF
#    define INF 0x7fffffff
#endif
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

    void solve(int s, int t) {
        this->s = s, this->t = t;
        flow = cost = 0;
        std::fill(H, H + n + 1, 0);
        while (dijkstra())
            ;
    }

    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; ++i)
            G[i].clear();
    }

    void addEdge(int u, int v, int cap, int cost) {
        G[u].push_back({v, cap, cost, SZ(G[v])});
        G[v].push_back({u, 0, -cost, SZ(G[u]) - 1});
    }

} mcmf;
/********************/
#include <cstdio>
using namespace std;
vector<int> p;
int w[MAXN], l[MAXN], r[MAXN];

int main() {
    int T, n, k, u, v;
    scanf("%d", &T);
    while (T--) {
        p.clear();
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &l[i], &r[i], w + i);
            p.push_back(l[i]);
            p.push_back(r[i]);
        }
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        int start = 0, target = p.size() + 1;
        mcmf.init(2 * target);
        for (int i = 1; i < target - 1; i++)
            mcmf.addEdge(i, i + 1, INF, 0);
        mcmf.addEdge(start, 1, k, 0);
        mcmf.addEdge(target - 1, target, k, 0);
        for (int i = 1; i <= n; i++) {
            u = lower_bound(p.begin(), p.end(), l[i]) - p.begin();
            v = lower_bound(p.begin(), p.end(), r[i]) - p.begin();
            mcmf.addEdge(u, v, 1, -w[i]);
        }
        mcmf.solve(start, target);
        printf("%d\n", -mcmf.cost);
    }
}