// Farm Tour

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> P;
struct edge {
    int to, cap, cost, rev;
};
int V;
const int MAX_V = 50000;
const int INF = 0x7fffffff;
vector<edge> G[MAX_V];
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];
void addEdge(int from, int to, int cap, int cost) {
    G[from].push_back((edge){to, cap, cost, G[to].size()});
    G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
}
int minCostFlow(int s, int t, int f) {
    int res = 0;
    fill(h, h + V, 0);
    while (f > 0) {
        priority_queue<P, vector<P>, greater<P> > que;
        fill(dist, dist + V, INF);
        dist[s] = 0;
        que.push(P(0, s));
        while (!que.empty()) {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first)
                continue;
            for (int i = 0; i < (int)G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 &&
                    dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        if (dist[t] == INF) {
            return -1;
        }
        for (int v = 0; v < V; v++) {
            h[v] += dist[v];
        }
        int d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}
int N, M;
const int MAX_M = 10000 + 5;
int a[MAX_M], b[MAX_M], c[MAX_M];
void solve() {
    int s = 0, t = N - 1;
    V = N;
    for (int i = 0; i < M; i++) {
        addEdge(a[i] - 1, b[i] - 1, 1, c[i]);
        addEdge(b[i] - 1, a[i] - 1, 1, c[i]);
    }
    printf("%d\n", minCostFlow(s, t, 2));
}
int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d", a + i, b + i, c + i);
    }
    solve();
}