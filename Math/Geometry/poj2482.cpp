// Stars in Your Window

#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 10000
typedef long long i64;

i64 xs[MAXN];
i64 ys[MAXN];
int cs[MAXN];
i64 X[MAXN * 2];
i64 Y[MAXN * 2];
struct Event {
    int x, bright, y1, y2;
} event[MAXN * 2];
bool operator<(const Event &a, const Event &b) { return a.x < b.x; }
int node_value[MAXN * 8], node_max[MAXN * 8];
void add(int from, int to, int v, int i, int l, int r) {
    if (from <= l && r <= to) {
        node_value[i] += v;
        node_max[i] += v;
        return;
    }
    int m = (l + r) >> 1;
    if (from <= m)
        add(from, to, v, i * 2, l, m);
    if (m < to)
        add(from, to, v, i * 2 + 1, m + 1, r);
    node_max[i] = max(node_max[i * 2], node_max[i * 2 + 1]) + node_value[i];
}

int main() {
    int n, W, H;
    while (~scanf("%d%d%d", &n, &W, &H)) {
        for (int i = 0; i < n; ++i) {
            scanf("%lld%lld%d", xs + i, ys + i, cs + i);
            xs[i] *= 2;
            ys[i] *= 2;
        }
        for (int i = 0; i < n; ++i) {
            X[i * 2] = xs[i] - W;
            X[i * 2 + 1] = xs[i] + W;
            Y[i * 2] = ys[i] - H;
            Y[i * 2 + 1] = ys[i] - 1 + H;
        }
        sort(X, X + n * 2);
        sort(Y, Y + n * 2);
        for (int i = 0; i < n; ++i) {
            event[i * 2] =
                Event{lower_bound(X, X + n * 2, xs[i] - W) - X, cs[i],
                      lower_bound(Y, Y + n * 2, ys[i] - H) - Y,
                      lower_bound(Y, Y + n * 2, ys[i] + H - 1) - Y};
            event[i * 2 + 1] =
                Event{lower_bound(X, X + n * 2, xs[i] + W) - X, -cs[i],
                      lower_bound(Y, Y + n * 2, ys[i] - H) - Y,
                      lower_bound(Y, Y + n * 2, ys[i] + H - 1) - Y};
        }
        sort(event, event + n * 2);
        int ans = 0;
        for (int i = 0; i < n * 2; i++) {
            add(event[i].y1, event[i].y2, event[i].bright, 1, 0, n * 2);
            ans = max(ans, node_max[1]);
        }
        printf("%d\n", ans);
    }
    return 0;
}