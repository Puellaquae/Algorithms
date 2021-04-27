#include <algorithm>
#include <cstdio>
#include <vector>

#define SZ(v) (int)v.size()

const int INF = 1e9;
const int MAXN = 1010;
const int MAXM = 1e5 + 10;

namespace MaxFlow {
struct Edge {
    int v, rev, f;
};

int n, s, t;
int cur[MAXM], dep[MAXN], gap[MAXN];
int flow;
std::vector<Edge> G[MAXN];

void add_edge(int u, int v, int f) {
    G[u].push_back({v, SZ(G[v]), f});
    G[v].push_back({u, SZ(G[u]) - 1, 0});
}

int dfs(int u, int lim) {
    if (u == t) {
        return lim;
    }
    int num = 0, f;
    for (int &i = cur[u], v; i < SZ(G[u]); ++i) {
        if (dep[v = G[u][i].v] == dep[u] - 1 && (f = G[u][i].f)) {
            f = dfs(v, std::min(lim - num, f));
            G[u][i].f -= f;
            G[v][G[u][i].rev].f += f;
            num += f;
            if (num == lim) {
                return num;
            }
        }
    }
    if (!--gap[dep[u]++]) {
        dep[s] = n + 1;
    }
    ++gap[dep[u]];
    cur[u] = 0;
    return num;
}

void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i)
        G[i].clear();
}

int solve(int _s, int _t) {
    s = _s, t = _t, flow = 0;
    for (int i = 0; i <= n; ++i)
        cur[i] = dep[i] = gap[i] = 0;
    for (gap[0] = n; dep[s] <= n; flow += dfs(s, INF))
        ;
        return flow;
}
}

using namespace MaxFlow;

int main() {
    int n, m, s, t;
    scanf("%d%d", &n, &m);
    s = n + n + 1, t = n + n + 2;
    init(n + n + 2);
    for (int i = 0, x, y; i < m; ++i) {
        scanf("%d%d", &x, &y);
        add_edge(x, y + n, 1);
    }
    for (int i = 1; i <= n; ++i) {
        add_edge(s, i, 1), add_edge(i + n, t, 1);
    }
    printf("%d\n", solve(s, t));
    return 0;
}
