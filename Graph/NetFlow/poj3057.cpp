// Evacuation

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int dx[4] = {-1, 0, 0, 1}, dy[4] = {0, -1, 1, 0};
int X, Y;
const int MAX_X = 12;
const int MAX_Y = 12;
char field[MAX_X][MAX_Y + 1];
vector<int> dX, dY, pX, pY;
int dist[MAX_X][MAX_Y][MAX_X][MAX_Y];
int V;
const int MAX_V = 50000;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];
void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        int u = G[v][i], w = match[u];
        if (w < 0 || !used[w] && dfs(w)) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

void bfs(int x, int y, int d[MAX_X][MAX_Y]) {
    queue<int> qx, qy;
    d[x][y] = 0;
    qx.push(x);
    qy.push(y);
    while (!qx.empty()) {
        x = qx.front();
        qx.pop();
        y = qy.front();
        qy.pop();
        for (int k = 0; k < 4; k++) {
            int x2 = x + dx[k], y2 = y + dy[k];
            if (0 <= x2 && x2 < X && 0 <= y2 && y2 < Y &&
                field[x2][y2] == '.' && d[x2][y2] < 0) {
                d[x2][y2] = d[x][y] + 1;
                qx.push(x2);
                qy.push(y2);
            }
        }
    }
}
void solve() {
    scanf("%d%d", &X, &Y);
    for (int i = 0; i < X; i++) {
        scanf("%s", field[i]);
    }
    int n = X * Y;
    dX.clear();
    dY.clear();
    pX.clear();
    pY.clear();
    memset(dist, -1, sizeof(dist));
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            if (field[x][y] == 'D') {
                dX.push_back(x);
                dY.push_back(y);
                bfs(x, y, dist[x][y]);
            } else if (field[x][y] == '.') {
                pX.push_back(x);
                pY.push_back(y);
            }
        }
    }
    int d = dX.size(), p = pX.size();
    V=X*Y*d+p;
    for(int v=0; v<V; ++v) G[v].clear();
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < p; j++) {
            if (dist[dX[i]][dY[i]][pX[j]][pY[j]] >= 0) {
                for (int k = dist[dX[i]][dY[i]][pX[j]][pY[j]]; k <= n; k++) {
                    add_edge((k - 1) * d + i, n * d + j);
                }
            }
        }
    }
    if (p == 0) {
        printf("0\n");
        return;
    }
    int num = 0;
    memset(match, -1, sizeof(match));
    for (int v = 0; v < n * d; v++) {
        memset(used, 0, sizeof(used));
        if (dfs(v)) {
            if (++num == p) {
                printf("%d\n", v / d + 1);
                return;
            }
        }
    }
    printf("impossible\n");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}