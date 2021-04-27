// The Closest Pair Problem

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
typedef pair<double, double> Point;
#ifndef DBL_MAX
#    define DBL_MAX 1.79769e+308
#endif
#ifndef INF
#    define INF DBL_MAX
#endif
const int MAX_N = 10005;
int N;
Point A[MAX_N];
bool CompareY(Point a, Point b) { return a.second < b.second; }
double ClosestPair(Point *a, int n) {
    if (n <= 1)
        return INF;
    int m = n / 2;
    double x = a[m].first;
    double d = min(ClosestPair(a, m), ClosestPair(a + m, n - m));
    inplace_merge(a, a + m, a + n, CompareY);
    vector<Point> b;
    for (int i = 0; i < n; i++) {
        if (fabs(a[i].first - x) >= d)
            continue;
        for (int j = 0; j < b.size(); j++) {
            double dx = a[i].first - b[b.size() - j - 1].first;
            double dy = a[i].second - b[b.size() - j - 1].second;
            if (dy >= d)
                break;
            d = min(d, sqrt(dx * dx + dy * dy));
        }
        b.push_back(a[i]);
    }
    return d;
}
void Solve() {
    sort(A, A + N);
    double ans = ClosestPair(A, N);
    if (ans < 10000.) {
        printf("%.4f\n", ans);
    } else {
        puts("INFINITY");
    }
}
int main() {
    while (scanf("%d", &N) != EOF && N != 0) {
        for (int i = 0; i < N; i++) {
            scanf("%lf%lf", &A[i].first, &A[i].second);
        }
        Solve();
    }
}