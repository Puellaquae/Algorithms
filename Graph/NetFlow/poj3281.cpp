// Dining

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_V = 50000;
struct edge {
    int to, cap, rev;
};
const int INF = 0x7fffffff;
vector<edge> G[MAX_V];
bool used[MAX_V];
void addEdge(int from, int to, int cap) {
    G[from].push_back({to, cap, G[to].size()});
    G[to].push_back({from, 0, G[from].size() - 1});
}
int dfs(int v, int t, int f) {
    if (v == t)
        return f;
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    for (;;) {
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, INF);
        if (f == 0)
            return flow;
        flow += f;
    }
}

int N, F, D;
const int MAX_N = 100 + 5;
const int MAX_F = 100 + 5;
const int MAX_D = 100 + 5;
bool likeF[MAX_N][MAX_F];
bool likeD[MAX_N][MAX_D];
void solve() {
    int s = N * 2 + F + D;
    int t = s + 1;
    for (int i = 0; i < F; i++) {
        addEdge(s, N * 2 + i, 1);
    }
    for (int i = 0; i < D; i++) {
        addEdge(N * 2 + F + i, t, 1);
    }
    for (int i = 0; i < N; i++) {
        addEdge(i, N + i, 1);
        for (int j = 0; j < F; j++) {
            if (likeF[i][j])
                addEdge(N * 2 + j, i, 1);
        }
        for (int j = 0; j < D; j++) {
            if (likeD[i][j])
                addEdge(N + i, N * 2 + F + j, 1);
        }
    }
    printf("%d\n", max_flow(s, t));
}
int main() {
    scanf("%d%d%d", &N, &F, &D);
    for (int i = 0; i < N; i++) {
        int fi, di;
        scanf("%d%d", &fi, &di);
        for (int j = 0; j < fi; j++) {
            int ci;
            scanf("%d", &ci);
            likeF[i][ci-1] = true;
        }
        for (int j = 0; j < di; j++) {
            int ci;
            scanf("%d", &ci);
            likeD[i][ci-1] = true;
        }
    }
    solve();
}