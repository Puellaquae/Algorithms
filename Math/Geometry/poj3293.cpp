// Rectilinear polygon

#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 100050;
struct Point {
    int x, y, id;
};
bool cmpX(Point a, Point b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
bool cmpY(Point a, Point b) {
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}
struct VerticalLine {
    int x, y1, y2;
} lines[MAXN];

Point points[MAXN];
int link_x[MAXN], link_y[MAXN];
bool check_intersect(Point a, Point b, int linecnt) {
    for (int i = 0; i < linecnt; i++) {
        if (a.x < lines[i].x && b.x > lines[i].x && lines[i].y1 < a.y &&
            lines[i].y2 > a.y)
            return true;
    }
    return false;
}
int n;
int scanX(int &linecnt) {
    sort(points, points + n, cmpX);
    int pointInLine = 1;
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x != points[i - 1].x) {
            if (pointInLine & 1) {
                return -1;
            }
            pointInLine = 1;
        } else {
            pointInLine++;
            if (pointInLine % 2 == 0) {
                sum += points[i].y - points[i - 1].y;
                link_x[points[i].id] = points[i - 1].id;
                link_x[points[i - 1].id] = points[i].id;
                lines[linecnt++] =
                    VerticalLine{points[i].x, points[i - 1].y, points[i].y};
            }
        }
    }
    return sum;
}
int scanY(int &linecnt) {
    sort(points, points + n, cmpY);
    int pointInLine = 1;
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y != points[i - 1].y) {
            if (pointInLine & 1) {
                return -1;
            }
            pointInLine = 1;
        } else {
            pointInLine++;
            if (pointInLine % 2 == 0) {
                sum += points[i].x - points[i - 1].x;
                link_y[points[i].id] = points[i - 1].id;
                link_y[points[i - 1].id] = points[i].id;
                if (check_intersect(points[i - 1], points[i], linecnt)) {
                    return -1;
                }
            }
        }
    }
    return sum;
}
int solve() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
        points[i].id = i;
    }
    int ln = 0;
    int x = scanX(ln);
    if (x == -1)
        return -1;
    int y = scanY(ln);
    if (y == -1)
        return -1;
    int cur = 0, linkcnt = 0;
    bool xflag = false;
    do {
        cur = xflag ? link_x[cur] : link_y[cur];
        xflag = !xflag;
        linkcnt++;
    } while (cur != 0);
    if (linkcnt != n)
        return -1;
    return x + y;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        printf("%d\n", solve());
    }
}