//传送带
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const double EPS = 1e-7;
struct Point {
    double x, y;
    Point(){};
    Point(double a, double b) { x = a, y = b; }
};
Point A, B, C, D;
double P, Q, R;
double Distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double Time(Point a, Point b) { return Distance(a, b) / P; }
double Time(Point f, Point e, Point d) { return Distance(f, d) / Q + Distance(f, e) / R; }

double FindF(Point l, Point r, Point e) {
    double a, b;
    do {
        Point m1 = Point((l.x + r.x) / 2, (l.y + r.y) / 2);
        Point m2 = Point((m1.x + r.x) / 2, (m1.y + r.y) / 2);
        a = Time(m1, e, D);
        b = Time(m2, e, D);
        if (a < b) {
            r = m2;
        } else {
            l = m1;
        }
    } while (abs(a - b) > EPS);
    return a;
}

double FindE(Point l, Point r) {
    while (true) {
        Point m1 = Point((l.x + r.x) / 2, (l.y + r.y) / 2);
        Point m2 = Point((m1.x + r.x) / 2, (m1.y + r.y) / 2);
        double a, b;
        a = FindF(C, D, m1);
        b = FindF(C, D, m2);
        if (abs(a - b) <= EPS) {
            return a + Time(A, m2);
        }
        if (a + Time(A, m1) < b + Time(A, m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
}

int main() {
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
    cin >> P >> Q >> R;
    printf("%.2lf\n", FindE(A, B));
    return 0;
}
