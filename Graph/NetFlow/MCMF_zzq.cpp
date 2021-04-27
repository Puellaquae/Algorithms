/* MCMF_zzq
 *
 * 调用：
 *     init(n) 初始化
 *     addEdge(u, v, cap, cost) 建图
 *     solve(s, t) 计算答案
 *     cost - 费用， flow - 流量
 */

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

const int MAXN=100000;
const int MAXM=100000;
const int INF;
#define SZ(v) (int)v.size()

struct MCMF {
    int N, M, S, T;
    int flow, ans, sum;
    typedef std::vector<int> vi;
    vi G[MAXN];
    int dist[MAXN], cap[MAXM], cost[MAXM], to[MAXM];
    bool aug[MAXN];

    void _add_edge(int a, int b, int c, int d) {
        G[a].push_back(++M), to[M] = b, cap[M] = c, cost[M] = d;
    }

    // u, v, capacity, cost
    void add_edge(int a, int b, int c, int d) {
        _add_edge(a, b, c, d), _add_edge(b, a, 0, -d);
    }

    int dfs(int u, int lim) {
        if (!lim) return 0;
        if (u == T) return ans += lim * sum, lim;
        int f = 0, v;
        aug[u] = true;
        for (auto e : G[u])
            if (!cost[e] && cap[e] && !aug[v = to[e]]) {
                int t = dfs(v, std::min(lim - f, cap[e]));
                cap[e] -= t, cap[e ^ 1] += t, f += t;
                if (f == lim) break;
            }
        if (f == lim) aug[u] = false;
        return f;
    }

    bool augment() {
        typedef std::pair<int,int> pii;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
        std::fill(dist, dist + N + 1, INF);
        q.push({dist[T] = 0, T});
        while (!q.empty()) {
            pii x = q.top();
            q.pop();
            if (dist[x.second] != x.first) continue;
            int &u = x.second, dt, v;
            for (int e : G[u])
                if (cap[e ^ 1] && (dt = dist[u] - cost[e]) < dist[v = to[e]])
                    q.push({dist[v] = dt, v});
        }
        sum += dist[S];
        for (int i = 0; i <= N; ++i)
            for (int e : G[i]) cost[e] += dist[to[e]] - dist[i];
        return dist[S] != INF;
    }

    void init(int n) {
        N = n, M = 1;
        for (int i = 0; i <= n; ++i) G[i].clear();
    }

    void solve(int _s, int _t) {
        int res;
        S = _s, T = _t;
        flow = ans = sum = 0;
        do
            do
                std::fill(aug, aug + N + 1, 0);
            while (flow += (res = dfs(S, INF)), res > 0);
        while (augment());
    }
} mcmf;