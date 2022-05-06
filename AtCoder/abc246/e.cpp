#include <cstdio>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cstring>
using namespace std;

constexpr char EMPTY = '.';
constexpr int N = 1507;
char b[N][N];
bool vis[N][N];

int main() {
    int n;
    int ax, ay, bx, by;
    scanf("%d", &n);
    scanf("%d%d", &ax, &ay);
    scanf("%d%d", &bx, &by);
    ax--;
    ay--;
    bx--;
    by--;
    for (int i = 0; i < n; i++) {
        scanf("%s", &b[i]);
    }
    if (abs(ax - bx + ay - by) % 2 != 0) {
        cout << -1 << endl;
        return 0;
    }
    queue<tuple<int, int, int> > q;
    memset(vis, sizeof(vis), 0);
    auto safe = [n](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < n && b[x][y] == EMPTY;
    };
    vis[ax][ay] = true;
    q.emplace(ax, ay, 0);
    while (!q.empty()) {
        int cx = get<0>(q.front());
        int cy = get<1>(q.front());
        int step = get<2>(q.front());
        q.pop();
        if (cx == bx && cy == by) {
            cout << step << endl;
            return 0;
        }
        int ds[][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (auto &dd : ds) {
            for (int d = 1;; d++) {
                int nx = cx + dd[0] * d;
                int ny = cy + dd[1] * d;
                if (!safe(nx, ny)) {
                    break;
                }
                if (!vis[nx][ny]) {
                    vis[nx][ny] = true;
                    q.emplace(nx, ny, step + 1);
                }
            }
        }
    }
    cout << -1 << endl;
}