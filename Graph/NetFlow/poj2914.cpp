//Minimum Cut

/*******************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAX_N 500 + 16
#define INF 0x3f3f3f3f

int G[MAX_N][MAX_N];
int v[MAX_N];
int w[MAX_N];
bool visited[MAX_N];

int stoer_wagner(int n) {
    int min_cut = INF;
    for (int i = 0; i < n; i++) {
        v[i] = i;
    }
    while (n > 1) {
        int pre = 0;
        memset(visited, 0, sizeof(visited));
        memset(w, 0, sizeof(w));
        for (int i = 1; i < n; i++) {
            int k = -1;
            for (int j = 1; j < n; j++) {
                if (!visited[v[j]]) {
                    w[v[j]] += G[v[pre]][v[j]];
                    if (k == -1 || w[v[k]] < w[v[j]]) {
                        k = j;
                    }
                }
            }
            visited[v[k]] = true;
            if (i == n - 1) {
                const int s = v[pre], t = v[k];
                min_cut = min(min_cut, w[t]);
                for (int j = 0; j < n; j++) {
                    G[s][v[j]] += G[v[j]][t];
                    G[v[j]][s] += G[v[j]][t];
                }
                v[k] = v[--n];
            }
            pre = k;
        }
    }
    return min_cut;
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(G, 0, sizeof(G));
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            G[u][v] += w;
            G[v][u] += w;
        }
        printf("%d\n", stoer_wagner(n));
    }
    return 0;
}