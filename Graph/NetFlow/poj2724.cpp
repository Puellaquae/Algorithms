// Purifying Machine

/************/
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 10 + 16
#define MAX_M 2000 + 16

#define MAX_V MAX_M * 2
int V;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for (vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
        int u = *it, w = match[u];
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

void clear() {
    for (int i = 0; i < V; ++i) {
        G[i].clear();
    }
}

vector<int> operations;
char buffer[MAX_N];

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) != EOF && N && M) {
        operations.clear();
        for (int ifor = 0; ifor < M; ifor++) {
            scanf(" %s ", buffer);
            int t = 0;
            for (int i = 0; i < N; ++i) {
                if (buffer[i] == '1') {
                    t += 1 << (N - i - 1);
                }
            }
            operations.push_back(t);
            for (int i = 0; i < N; ++i) {
                if (buffer[i] == '*') {
                    t += 1 << (N - i - 1);
                }
            }
            operations.push_back(t);
        }
        sort(operations.begin(), operations.end());
        operations.erase(unique(operations.begin(), operations.end()),
                         operations.end());
        V = operations.size();
        clear();
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                int diff = operations[i] ^ operations[j];
                if ((diff & (-diff)) == diff) {
                    add_edge(i, j);
                }
            }
        }
        printf("%d\n", V - bitch());
    }
    return 0;
}