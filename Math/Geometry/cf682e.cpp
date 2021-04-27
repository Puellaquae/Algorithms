// Alyona and ztriangles

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
#define int long long
typedef pair<int, int> point;
point operator-(point a, point b) {
    return make_pair(a.first - b.first, a.second - b.second);
}

int det(point a, point b) { return a.first * b.second - a.second * b.first; }

vector<point> convex_hull(point *ps, int n) {
    sort(ps, ps + n);
    int k = 0;
    vector<point> qs(n * 2);
    for (int i = 0; i < n; i++) {
        while (k > 1 && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0)
            k--;
        qs[k++] = ps[i];
    }
    for (int i = n - 2, t = k; i >= 0; i--) {
        while (k > t && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0)
            k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}
const int MAXN = 5050;
point points[MAXN];

int area(point a, point b, point c) {
    return abs((b.first - a.first) * (c.second - a.second) -
               (c.first - a.first) * (b.second - a.second));
}

#define OUT &
double findMaxTri(int n, point OUT a, point OUT b, point OUT c) {
    vector<point> ps = convex_hull(points, n);
    int psc = (int)ps.size();
    bool flag = true;
    int ai = 0, bi = 1, ci = 2;
    int ans = area(ps[ai], ps[bi], ps[ci]);
    while (flag) {
        flag = false;
        for (int i = 0; i < psc; i++) {
            int tmp;
            tmp = area(ps[ai], ps[bi], ps[i]);
            if (tmp > ans) {
                ans = tmp;
                ci = i;
                flag = true;
            }
            tmp = area(ps[ai], ps[i], ps[ci]);
            if (tmp > ans) {
                ans = tmp;
                bi = i;
                flag = true;
            }
            tmp = area(ps[i], ps[bi], ps[ci]);
            if (tmp > ans) {
                ans = tmp;
                ai = i;
                flag = true;
            }
        }
    }
    a = ps[ai];
    b = ps[bi];
    c = ps[ci];
    return ans;
}
#undef int
int main() {
    int n, s;
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", &points[i].first, &points[i].second);
    }
    point a, b, c;
    findMaxTri(n, a, b, c);
    printf("%lld %lld\n", a.first + b.first - c.first,
           a.second + b.second - c.second);
    printf("%lld %lld\n", a.first + c.first - b.first,
           a.second + c.second - b.second);
    printf("%lld %lld\n", b.first + c.first - a.first,
           b.second + c.second - a.second);
}