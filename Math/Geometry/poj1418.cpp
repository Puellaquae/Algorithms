// Viva Confetti

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using std::vector;
#define EPS 1e-13
#define PI 3.14159265358979323
inline bool flesser_0(double a) { return a < -EPS; }
inline bool fnot_greater_0(double a) { return a < EPS; }
inline bool fequal(double a, double b) { return fabs(a - b) < EPS; }

const int MAXN = 100005;
struct Circle {
    double x, y, r;
} circles[MAXN];
bool visible[MAXN];
inline double dis(Circle a, Circle b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline double normalize(double r) {
    while (r < 0.0)
        r += 2 * PI;
    while (r >= 2 * PI)
        r -= 2 * PI;
    return r;
}
inline double arg(Circle a, Circle b) { return atan2(a.y - b.y, a.x - b.x); }
int hit_test(Circle c,int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (dis(circles[i], c) < circles[i].r)
            return i;
    }
    return -1;
}

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        memset(visible, 0, sizeof(visible));
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf%lf", &circles[i].x, &circles[i].y, &circles[i].r);
        }
        for (int i = 0; i < n; i++) {
            vector<double> rads;
            rads.push_back(0.);
            rads.push_back(2. * PI);
            for (int j = 0; j < n; j++) {
                double a = circles[i].r;
                double b = dis(circles[i], circles[j]);
                double c = circles[j].r;
                if (a + b < c || a + c < b || b + c < a)
                    continue;
                double d = arg(circles[j], circles[i]);
                double e = acos((a * a + b * b - c * c) / (2. * a * b));
                rads.push_back(normalize(d + e));
                rads.push_back(normalize(d - e));
            }
            sort(rads.begin(), rads.end());
            for (int j = 0; j < (int)rads.size() - 1; j++) {
                double rad = (rads[j + 1] + rads[j]) / 2.;
                for (int k = -1; k <= 1; k += 2) {
                    int t = hit_test(
                        Circle{
                            circles[i].x + (circles[i].r + EPS * k) * cos(rad),
                            circles[i].y + (circles[i].r + EPS * k) * sin(rad),
                            0.},
                        n);
                    if (t != -1) {
                        visible[t] = true;
                    }
                }
            }
        }
        std::cout << std::count(visible, visible + n, true) << std::endl;
    }
}