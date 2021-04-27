// Wall

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
typedef pair<int, int> point;
point operator-(point a, point b) {
    return make_pair(a.first - b.first, a.second - b.second);
}

int det(point a, point b) { return a.first * b.second - a.second * b.first; }
int dot(point a, point b) { return a.first * b.first + a.second * b.second; }
double dis(point a, point b) {
    return sqrt((a.first - b.first) * (a.first - b.first) +
                (a.second - b.second) * (a.second - b.second));
}
double abs(point a) { return sqrt(a.first * a.first + a.second * a.second); }

double deg(point a, point b, point c) {
    point l = a - b, r = b - c;
    double deg = dot(l, r) / abs(l) / abs(r);
    deg = acos(deg);
    return deg;
}
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

const int MAXN = 1005;
point points[MAXN];

double solve() {
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &points[i].first, &points[i].second);
    }
    vector<point> ps = convex_hull(points, n);
    int psc = (int)ps.size();
    double ans = 0.;
    for (int i = 0; i < psc - 1; i++) {
        ans += dis(ps[i], ps[i + 1]);
    }
    ans += dis(ps.back(), ps[0]);
    double degs = 0.;
    for (int i = 0; i < psc - 2; i++) {
        degs += deg(ps[i], ps[i + 1], ps[i + 2]);
    }
    degs += deg(ps[psc - 2], ps[psc - 1], ps[0]);
    degs += deg(ps[psc - 1], ps[0], ps[1]);
    ans += degs * l;
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        printf("%.0f\n", solve());
        if (T) {
            printf("\n");
        }
    }
}