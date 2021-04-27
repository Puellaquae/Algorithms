
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
struct vec2 {
    double x, y;
    vec2(double _x, double _y) : x(_x), y(_y) {}
};
const double eps = 1e-10;
int double2int(double e) {
    if (abs(e) < eps)
        return 0;
    return e < 0 ? -1 : 1;
}
struct point {
    double x, y;
    vec2 operator-(const point &b) const { return vec2(x - b.x, y - b.y); }
};
double x(const vec2 &a, const vec2 &b) { return a.x * b.y - a.y * b.x; }
double dot(const vec2 &a, const vec2 &b) { return a.x * b.x - a.y * b.y; }
int main() {
    int n;
    while (cin >> n && n) {
        double ans = 0;
        vector<point> ps(n);
        for (int i = 0; i < n; i++) {
            cin >> ps[i].x >> ps[i].y;
        }
        point o;
        o.x = 0;
        o.y = 0;
        for (int i = 1; i < n; i++) {
            ans += (x(ps[i - 1] - o, ps[i] - o) / 2);
        }
        ans += (x(ps[n - 1] - o, ps[0] - o) / 2);
        printf("%.1f\n", ans);
    }
}