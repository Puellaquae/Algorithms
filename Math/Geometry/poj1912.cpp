// A highway and the seven dwarfs

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct point {
    double first, second;
};
bool operator<(point a, point b) {
    if (fabs(a.first - b.first) < 1e-10) {
        return a.second < b.second;
    }
    return a.first < b.first;
}
point operator-(point a, point b) {
    point ans;
    ans.first = a.first - b.first;
    ans.second = a.second - b.second;
    return ans;
}

double det(point a, point b) { return a.first * b.second - a.second * b.first; }
#define PI 3.14159265358979323846
#define EPS 1e-10
double normalize(double r) {
    if (r < -PI / 2.0 + EPS)
        r += PI * 2;
    return r;
}

inline double atan2(const point &p) {
    return normalize(atan2(p.second, p.first));
}

inline bool double_cmp(double a, double b) { return a + EPS < b; }

vector<point> convex_hull(point *ps, int n) {
    sort(ps, ps + n);
    int k = 0;
    vector<point> qs(n * 2);
    for (int i = 0; i < n; i++) {
        while (k > 1 && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0.)
            k--;
        qs[k++] = ps[i];
    }
    for (int i = n - 2, t = k; i >= 0; i--) {
        while (k > t && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0.)
            k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}

bool intersetQ(point a, point b, point x, point y) {
    return det(a - x, y - x) * det(y - x, b - x) > -EPS;
}

const int MAXN = 100050;
point points[MAXN];
double as[MAXN];
int main() {
    int n;
    point a, b;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &points[i].first, &points[i].second);
    }
    vector<point> ps;
    int psc = 0;
    if (n > 1) {
        ps = convex_hull(points, n);
        psc = ps.size();
        ps.push_back(ps[0]);
    }
    for (int i = 0; i < psc; i++) {
        as[i] = atan2(ps[i + 1] - ps[i]);
    }
    sort(as, as + psc, double_cmp);
    while (~scanf("%lf%lf%lf%lf", &a.first, &a.second, &b.first, &b.second)) {
        if (n < 2) {
            puts("GOOD");
            continue;
        }
        int i = upper_bound(as, as + psc, atan2(b - a), double_cmp) - as;
        int j = upper_bound(as, as + psc, atan2(a - b), double_cmp) - as;
        puts(intersetQ(ps[i], ps[j], a, b) ? "BAD" : "GOOD");
    }
}