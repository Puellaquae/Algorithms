// Evacuation Plan
// From book

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
const int INF = 0x3fffffff;
const int MAX_N = 100 + 5;
const int MAX_M = 100 + 5;
const int MAX_V = MAX_N + MAX_M + 1;
int N, M;
int X[MAX_N], Y[MAX_N], B[MAX_N];
int P[MAX_M], Q[MAX_M], C[MAX_M];
int E[MAX_N][MAX_M];
int g[MAX_V][MAX_V];
int prev[MAX_V][MAX_V];
bool used[MAX_V];
void solve() {
    int V = N + M + 1;
    for (int i = 0; i < V; i++) {
        std::fill(g[i], g[i] + V, INF);
    }
    for (int j = 0; j < M; j++) {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            int c = abs(X[i] - P[j]) + abs(Y[i] - Q[j]) + 1;
            g[i][N + j] = c;
            if (E[i][j] > 0) {
                g[N + j][i] = -c;
            }
            sum += E[i][j];
        }
        if (sum > 0) {
            g[N + M][N + j] = 0;
        }
        if (sum < C[j]) {
            g[N + j][N + M] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            prev[i][j] = i;
        }
    }
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (g[i][j] > g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                    prev[i][j] = prev[k][j];
                    if (i == j && g[i][i] < 0) {
                        std::fill(used, used + V, false);
                        for (int v = i; !used[v]; v = prev[i][v]) {
                            used[v] = true;
                            if (v != N + M && prev[i][v] != N + M) {
                                if (v >= N) {
                                    E[prev[i][v]][v - N]++;
                                } else {
                                    E[v][prev[i][v] - N]--;
                                }
                            }
                        }
                        printf("SUBOPTIMAL\n");
                        for (int x = 0; x < N; x++) {
                            for (int y = 0; y < M; y++) {
                                printf("%d%c", E[x][y],
                                       y + 1 == M ? '\n' : ' ');
                            }
                        }
                        return;
                    }
                }
            }
        }
    }
    printf("OPTIMAL\n");
}
int main() {
    while (~scanf("%d%d", &N, &M)) {
        for (int i = 0; i < N; i++) {
            scanf("%d%d%d", X + i, Y + i, B + i);
        }
        for (int i = 0; i < M; i++) {
            scanf("%d%d%d", P + i, Q + i, C + i);
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &E[i][j]);
            }
        }
        solve();
    }
}