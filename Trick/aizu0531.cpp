// Paint Color
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
bool m[10005][10005];
int X1[1005], Y1[1005], X2[1005], Y2[1005];
int W, H, N;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int compress(int *x1, int *x2, int w) {
    vector<int> xs;
    for (int i = 0; i < N; i++) {
        for (int d = -1; d <= 1; d++) {
            int tx1 = x1[i] + d, tx2 = x2[i] + d;
            if (tx1 >= 1 && tx1 <= w) {
                xs.push_back(tx1);
            }
            if (tx2 >= 1 && tx2 <= w) {
                xs.push_back(tx2);
            }
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    for (int i = 0; i < N; i++) {
        x1[i] = find(xs.begin(), xs.end(), x1[i]) - xs.begin();
        x2[i] = find(xs.begin(), xs.end(), x2[i]) - xs.begin();
    }
    return xs.size();
}
int main() {
    while (~scanf("%d%d", &W, &H) && W && H) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d%d%d%d", &X1[i], &Y1[i], &X2[i], &Y2[i]);
            X1[i]++, Y1[i]++;
        }
        W = compress(X1, X2, W);
        H = compress(Y1, Y2, H);
        memset(m, false, sizeof(m));
        for (int i = 0; i < N; i++) {
            for (int y = Y1[i]; y <= Y2[i]; y++) {
                for (int x = X1[i]; x <= X2[i]; x++) {
                    m[y][x] = true;
                }
            }
        }
        int ans = 0;

        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (m[y][x])
                    continue;
                ans++;
                m[y][x] = true;
                queue<pair<int, int> > Q;
                Q.push(make_pair(x, y));
                while (!Q.empty()) {
                    int sx = Q.front().first, sy = Q.front().second;
                    Q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nx = sx + dx[i];
                        int ny = sy + dy[i];
                        if (nx < 0 || ny < 0 || nx >= W || ny >= H)
                            continue;
                        if (m[ny][nx])
                            continue;
                        Q.push(make_pair(nx, ny));
                        m[ny][nx] = true;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}