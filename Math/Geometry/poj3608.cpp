// Bridge Across Islands

#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>
using namespace std;

#define MAX_N 10000 + 16
#define INF 0x3F3F3F3F
#define EPS 1E-10

struct Point {
    double x, y;
    double dot(const Point &p) { return x * p.x + y * p.y; }
    double det(const Point &p) { return x * p.y - y * p.x; }
};


Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
}

Point P[MAX_N], Q[MAX_N];

inline double ABdetAC(Point A, Point B, Point C) { return (B - A).det(C - A); }

inline double ABdotAC(Point A, Point B, Point C) { return (B - A).dot(C - A); }

inline double dist(Point A, Point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

inline void anticlockwise_sort(Point *p, int N) {
    for (int i = 0; i < N - 2; i++) {
        double tmp = ABdetAC(p[i], p[i + 1], p[i + 2]);
        if (tmp > EPS)
            return;
        if (tmp < -EPS) {
            reverse(p, p + N);
            return;
        }
    }
}

inline double point_to_line(Point A, Point B, Point C) {
    if (dist(A, B) < EPS)
        return dist(B, C);
    if (ABdotAC(A, B, C) < -EPS)
        return dist(A, C);
    if (ABdotAC(B, A, C) < -EPS)
        return dist(B, C);
    return fabs(ABdetAC(A, B, C) / dist(A, B));
}

inline double line_to_line(Point A, Point B, Point C, Point D) {
    return min(min(point_to_line(A, B, C), point_to_line(A, B, D)),
               min(point_to_line(C, D, A), point_to_line(C, D, B)));
}

double solve(int n, int m) {
    int yminP = 0, ymaxQ = 0;
    for (int i = 0; i < n; i++)
        if (P[i].y < P[yminP].y)
            yminP = i;
    for (int i = 0; i < m; i++)
        if (Q[i].y > Q[ymaxQ].y)
            ymaxQ = i;
    P[n] = P[0];
    Q[m] = Q[0];
    double ans = INF;
    for (int i = 0; i < n; ++i) {
        while (ABdetAC(P[yminP + 1], Q[ymaxQ + 1], P[yminP]) - ABdetAC(P[yminP + 1], Q[ymaxQ], P[yminP]) > EPS) {
            ymaxQ = (ymaxQ + 1) % m;
        }
        ans = min(ans,
                  line_to_line(P[yminP], P[yminP + 1], Q[ymaxQ], Q[ymaxQ + 1]));
        yminP = (yminP + 1) % n;
    }
    return ans;
}

int main() {
    int N, M;
    while (~scanf("%d%d", &N, &M) && N + M) {
        for (int i = 0; i < N; ++i) {
            scanf("%lf%lf", &P[i].x, &P[i].y);
        }
        for (int i = 0; i < M; ++i) {
            scanf("%lf%lf", &Q[i].x, &Q[i].y);
        }
        anticlockwise_sort(P, N);
        anticlockwise_sort(Q, M);
        printf("%.5f\n", solve(N, M));
    }
    return 0;
}