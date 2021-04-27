// Game

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 100000 + 50;
typedef int T;
struct Point {
    T x, y;
    int id;
    bool operator<(const Point &b) const {
        if (x != b.x)
            return x < b.x;
        return y < b.y;
    }
    T dot(const Point &p) const { return x * p.x + y * p.y; }
    T det(const Point &p) const { return x * p.y - y * p.x; }
};

Point operator-(const Point &a, const Point &b) {
    return Point{a.x - b.x, a.y - b.y};
}
vector<Point> convex_hull(Point *ps, int n) {
    sort(ps, ps + n);
    int k = 0;
    vector<Point> qs(n * 2);
    for (int i = 0; i < n; i++) {
        while (k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
            k--;
        qs[k++] = ps[i];
    }
    for (int i = n - 2, t = k; i >= 0; i--) {
        while (k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
            k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}
Point ps[MAXN], tmp[MAXN];
T area(Point a, Point b, Point c) { return abs((b - a).det(c - a)); }
T area(const vector<Point> &ps) {
    T t = 0;
    for (int i = 2; i < ps.size(); i++) {
        t += area(ps[0], ps[i - 1], ps[i]);
    }
    return t;
}
int main() {
    int N;
    while (scanf("%d", &N), N > 0) {
        for (int i = 0; i < N; i++) {
            scanf("%d%d", &ps[i].x, &ps[i].y);
            ps[i].id = i;
        }
        memcpy(tmp, ps, N * sizeof(Point));
        vector<Point> nps = convex_hull(tmp, N);
        T ans = 0x3f3f3f3f;
        for (int i = 0; i < nps.size(); i++) {
            memcpy(tmp, ps, N * sizeof(Point));
            swap(tmp[nps[i].id], tmp[N - 1]);
            ans = min(ans, area(convex_hull(tmp, N - 1)));
        }
        printf("%d.%s\n", ans / 2, ans % 2 == 1 ? "50" : "00");
    }
}