// Priest John's Busiest Day

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define MAX_V 5010
int V;
vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];

void add_edge(int from, int to) {
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        if (!used[G[v][i]])
            dfs(G[v][i]);
    }
    vs.push_back(v);
}
void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    for (int i = 0; i < rG[v].size(); i++) {
        if (!used[rG[v][i]])
            rdfs(rG[v][i], k);
    }
}
int scc() {
    memset(used, 0, sizeof used);
    vs.clear();
    for (int v = 0; v < V; v++) {
        if (!used[v])
            dfs(v);
    }
    memset(used, 0, sizeof used);
    int k = 0;
    for (int i = vs.size() - 1; i >= 0; i--) {
        if (!used[vs[i]])
            rdfs(vs[i], k++);
    }
    return k;
}
#define MAX_N 1005

int N;
int S[MAX_N], T[MAX_N], D[MAX_N];
void solve() {
    V = N * 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (min(S[i] + D[i], S[j] + D[j]) > max(S[i], S[j])) {
                add_edge(i, N + j);
                add_edge(j, N + i);
            }
            if (min(S[i] + D[i], T[j]) > max(S[i], T[j] - D[j])) {
                add_edge(i, j);
                add_edge(N + j, N + i);
            }
            if (min(T[i], S[j] + D[j]) > max(T[i] - D[i], S[j])) {
                add_edge(N + i, j);
                add_edge(j, i);
            }
            if (min(T[i], T[j]) > max(T[i] - D[i], T[j] - D[j])) {
                add_edge(N + i, j);
                add_edge(N + j, i);
            }
        }
    }
    scc();
    for (int i = 0; i < N; i++) {
        if (cmp[i] == cmp[N + i]) {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
    for (int i = 0; i < N; i++) {
        if (cmp[i] > cmp[N + i]) {
            printf("%02d:%02d %02d:%02d\n", S[i] / 60, S[i] % 60,
                   (S[i] + D[i]) / 60, (S[i] + D[i]) % 60);
        } else {
            printf("%02d:%02d %02d:%02d\n", (T[i] - D[i]) / 60,
                   (T[i] - D[i]) % 60, T[i] / 60, T[i] % 60);
        }
    }
}
int main() {
    scanf("%d", &N);
    for (int i = 0, a, b, c, d; i < N; i++) {
        scanf("%d:%d %d:%d %d", &a, &b, &c, &d, D + i);
        S[i] = a * 60 + b;
        T[i] = c * 60 + d;
    }
    solve();
}