// Optimal Miking
// https://www.cnblogs.com/Lyush/archive/2013/04/30/3052077.html

#include <algorithm>
#include <cstdio>
#include <cstring>
namespace POJ2112 {
int K, C, M;
int N;
int mp[250][250];

struct Edge {
    int v, c, next;
};

Edge e[100000];
int index, head[250];
int lv[250];
int front, tail, que[250];
const int SS = 0, TT = 248;
const int INF = 0x3fffffff;

void insert(int a, int b, int c) {
    e[index].v = b, e[index].c = c;
    e[index].next = head[a];
    head[a] = index++;
}

void floyd() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            if (mp[i][k] != INF && i != k) {
                for (int j = 1; j <= N; j++) {
                    if (mp[k][j] != INF && j != k) {
                        mp[i][j] = std::min(mp[i][j], mp[i][k] + mp[k][j]);
                    }
                }
            }
        }
    }
}

void build(int threshold) {
    index = 0;
    memset(head, 0xff, sizeof head);
    for (int i = 1; i <= K; i++) {
        insert(SS, i, M);
        insert(i, SS, 0);
        for (int j = K + 1; j <= N; j++) {
            if (mp[i][j] <= threshold) {
                insert(i, j, 1);
                insert(j, i, 0);
            }
        }
    }
    for (int i = K + 1; i <= N; i++) {
        insert(i, TT, 1);
        insert(TT, i, 0);
    }
}

bool bfs() {
    front = tail = 0;
    memset(lv, 0xff, sizeof lv);
    lv[SS] = 0;
    que[tail++] = SS;
    while (front != tail) {
        int u = que[front++];
        for (int i = head[u]; i != -1; i = e[i].next) {
            if (!(~lv[e[i].v]) && e[i].c) {
                lv[e[i].v] = lv[u] + 1;
                if (e[i].v == TT) {
                    return true;
                }
                que[tail++] = e[i].v;
            }
        }
    }
    return ~lv[TT];
}

int dfs(int u, int sup) {
    if (u == TT) {
        return sup;
    }
    int tf = 0, f;
    for (int i = head[u]; i != -1; i = e[i].next) {
        if (lv[u] + 1 == lv[e[i].v] && e[i].c) {
            f = dfs(e[i].v, std::min(e[i].c, sup - tf));
            tf += f;
            e[i].c -= f;
            e[i ^ 1].c += f;
            if (f && tf == sup)
                return sup;
        }
    }
    if (!tf) {
        lv[u] = -1;
    }
    return tf;
}

int dinic() {
    int ret = 0;
    while (bfs()) {
        ret += dfs(SS, INF);
    }
    return ret;
}

int bisearch(int l, int r) {
    int mid, ret;
    while (l <= r) {
        mid = (l + r) / 2;
        build(mid);
        if (dinic() == C) {
            ret = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ret;
}
void solve() {
    while (~scanf("%d %d %d", &K, &C, &M)) {
        N = K + C;
        memset(mp, 0, sizeof mp);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                scanf("%d", &mp[i][j]);
                if (!mp[i][j]) {
                    mp[i][j] = INF;
                }
            }
        }
        floyd();
        printf("%d\n", bisearch(1, 1000000));
    }
}
} // namespace POJ2112
int main() {
    POJ2112::solve();
    return 0;
}
