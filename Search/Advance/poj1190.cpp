// 生日蛋糕

#include <iostream>
#include <queue>
using namespace std;
struct Content {
    int had_s, last_m, last_n, prev_r, prev_h;
};
int min_S = 0x7fffffff;
void dfs(Content c) {
    if (c.last_m == 0 && c.last_n == 0)
        min_S = min(min_S, c.had_s);
    if (c.last_m <= 0 || c.last_n <= 0)
        return;
    if (c.had_s >= min_S)
        return;
    if (c.last_m * (c.prev_h - 1) * (c.prev_r - 1) * (c.prev_r - 1) < c.last_n)
        return;
    for (int r = c.prev_r - 1; r >= c.last_m; r--) {
        for (int h = c.prev_h - 1; h >= c.last_m; h--) {
            dfs({c.had_s + 2 * r * h, c.last_m - 1, c.last_n - r * r * h, r,
                 h});
        }
    }
}
int main() {
    int N, M;
    cin >> N >> M;
    for (int r = 100; r >= M; r--) {
        for (int h = 10000; h >= M; h--) {
            dfs({r * r + 2 * r * h, M - 1, N - r * r * h, r, h});
        }
    }
    cout << (min_S == 0x7fffffff ? 0 : min_S) << endl;
}