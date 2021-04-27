// The Perfect Stall

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int MAX_V = 50000;
const int MAXN = 50000;
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

int N, M;
void solve() {
    mcmf.init(N + M + 2 );
    int s = N + M;
    int t = s + 1;
    //[0,N) cow
    //[N,N+M) stall
    for (int i = 0; i < N; i++) {
        mcmf.addEdge(s, i, 1 , 0);
    }
    for (int i = 0; i < M; i++) {
        mcmf.addEdge(i + N, t, 1, 0);
    }
    for (int i = 0; i < N; i++) {
        int S;
        scanf("%d", &S);
        while (S--) {
            int m;
            scanf("%d", &m);
            mcmf.addEdge(i, N + m - 1, 1,0);
        }
    }
    printf("%d\n", mcmf.solve(s, t));
}
int main() {
    while (~scanf("%d%d", &N, &M)) {
        solve();
    }
}