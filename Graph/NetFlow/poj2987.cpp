// Firing

/********************/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long LL;
#define MAX_V 5000 + 16
const LL LL_INF = 0x3f3f3f3f3f3f3f3f;
struct edge {
    int to, rev;
    LL cap;
    edge(int _to, LL _cap, int _rev)
        : to(_to), rev(_rev), cap(_cap) {}
};

vector<edge> G[MAX_V];
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from, int to, LL cap) {
    G[from].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(from, 0, G[from].size() - 1));
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (size_t i = 0; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

LL dfs(int v, int t, LL f) {
    if (v == t) {
        return f;
    }
    for (int &i = iter[v]; i < (int)G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            LL d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }

    return 0;
}

LL max_flow(int s, int t) {
    LL flow = 0;
    for (;;) {
        bfs(s);
        if (level[t] < 0) {
            return flow;
        }
        memset(iter, 0, sizeof(iter));
        LL f;
        while ((f = dfs(s, t, LL_INF)) > 0) {
            flow += f;
        }
    }
}

int vertex_count, visited[MAX_V];
void solve(int v) {
    ++vertex_count;
    visited[v] = true;
    for (int i = 0; i < int(G[v].size()); ++i) {
        const edge &e = G[v][i];
        if (e.cap > 0 && !visited[e.to]) {
            solve(e.to);
        }
    }
}
int main() {
    int n, m, w;
    LL W = 0;
    scanf("%d%d", &n, &m);
    const int s = 0, t = n + 1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w);
        if (w > 0) {
            W += w;
            add_edge(s, i, w);
        }
        if (w < 0) {
            add_edge(i, t, -w);
        }
    }

    int u, v;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v, LL_INF);
    }

    LL max_profit = W - max_flow(s, t);
    solve(s);
    printf("%d %lld\n", --vertex_count, max_profit);
    return 0;
}