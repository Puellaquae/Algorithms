// Muddy Fields

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1250 + 10;
int linker[MAXN];
bool used[MAXN];
struct node {
    int row, col;
} p[MAXN][MAXN];
int n;
int head[MAXN], tot;
struct Edge {
    int to, next;
} edge[MAXN * MAXN];
char mp[MAXN][MAXN];
void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}
void addEdge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
bool dfs(int u) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (!used[v]) {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v])) {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungry() {
    int res = 0;
    memset(linker, -1, sizeof(linker));
    for (int u = 1; u <= n; u++) {
        memset(used, false, sizeof(used));
        if (dfs(u))
            res++;
    }
    return res;
}
int main() {
    int r, c;
    while (~scanf("%d%d", &r, &c)) {
        n = 0;
        init();
        for (int i = 1; i <= r; i++) {
            scanf("%s", mp[i] + 1);
            for (int j = 1; j <= c; j++) {
                p[i][j].col = p[i][j].row = 0;
            }
        }
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (mp[i][j] == '*') {
                    if (j > 1 && mp[i][j - 1] == '*') {
                        p[i][j].row = p[i][j - 1].row;
                    } else {
                        p[i][j].row = ++n;
                    }
                }
            }
        }
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (mp[i][j] == '*') {
                    if (i > 1 && mp[i - 1][j] == '*') {
                        p[i][j].col = p[i - 1][j].col;
                    } else {
                        p[i][j].col = ++n;
                    }
                    addEdge(p[i][j].row, p[i][j].col);
                }
            }
        }
        printf("%d\n", hungry());
    }
    return 0;
}