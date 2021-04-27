// Kindergarten

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int MAX_V = 1000;
int V;
vector<int> _G[MAX_V];
int match[MAX_V];
bool used[MAX_V];
void addEdge(int u, int v) {
    _G[u].push_back(v);
    _G[v].push_back(u);
}
bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < _G[v].size(); i++) {
        int u = _G[v][i], w = match[u];
        if (w < 0 || !used[w] && dfs(w)) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}
int bitch() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int v = 0; v < V; v++) {
        if (match[v] < 0) {
            memset(used, 0, sizeof(used));
            if (dfs(v)) {
                res++;
            }
        }
    }
    return res;
}
int G, B, M;
const int MAX_GB = 201;
int relat[MAX_GB][MAX_GB];
int cnt = 1;
void solve() {
    memset(relat, 0, sizeof(relat));
    for (int i = 0, g, b; i < M; i++) {
        scanf("%d%d", &g, &b);
        relat[g - 1][b - 1] = true;
    }
    V = G + B;
    for (int i = 0; i < V; i++) {
        _G[i].clear();
    }
    for (int g = 0; g < G; g++) {
        for (int b = 0; b < B; b++) {
            if (!relat[g][b]) {
                addEdge(g, b + G);
            }
        }
    }
    printf("Case %d: %d\n", cnt++, V-bitch());
}
int main() {
    while (~scanf("%d%d%d", &G, &B, &M) && G && B && M) {
        solve();
    }
}