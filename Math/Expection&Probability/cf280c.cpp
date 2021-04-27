// Game on Tree

#include <cstdio>
constexpr int N = 1e5 + 100;

struct Edge {
    int to, from;
} e[N * 2];
int head[N], depth[N];

void addEdge(int x, int y) {
    static int cnt = 0;
    e[++cnt].from = y;
    e[cnt].to = head[x];
    head[x] = cnt;
}
void calcDepth(int x, int fa, int deep) {
    depth[x] = deep;
    for (int i = head[x]; i; i = e[i].to) {
        int u = e[i].from;
        if (u == fa)
            continue;
        calcDepth(u, x, deep + 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    calcDepth(1, 1, 1);
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += 1.0 / depth[i];
    printf("%.20f \n", ans);
    return 0;
}