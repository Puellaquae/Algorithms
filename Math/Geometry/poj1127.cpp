// Jack Straws
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
struct Dsu {
    Dsu(int n) : parent(n, -1) {}
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    void unit(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (parent[u] < parent[v])
            std::swap(u, v);
        parent[v] += parent[u];
        parent[u] = v;
    }

private:
    std::vector<int> parent;
};
using namespace std;
struct vec2 {
    double x, y;
    vec2(double _x, double _y) : x(_x), y(_y) {}
};
const double eps = 1e-10;
int double2int(double e) {
    if (fabs(e) < eps)
        return 0;
    else return e < 0 ? -1 : 1;
}
struct point {
    double x, y;
    vec2 operator-(const point &b) const { return vec2(x - b.x, y - b.y); }
    void input() { cin >> x >> y; }
};
double x(const vec2 &a, const vec2 &b) { return a.x * b.y - a.y * b.x; }
double dot(const vec2 &a, const vec2 &b) { return a.x * b.x + a.y * b.y; }
bool OnLineQ(const point &p, const point &a1, const point &a2) {
    return double2int(dot(p - a1, p - a2)) <= 0 ? 1 : 0;
}
bool CrossQ(const point &a1, const point &a2, const point &b1,
            const point &b2) {
    int c1 = double2int(x(a2 - a1, b1 - a1)),
        c2 = double2int(x(a2 - a1, b2 - a1)),
        c3 = double2int(x(b2 - b1, a1 - b1)),
        c4 = double2int(x(b2 - b1, a2 - b1));
    if (c1 || c2 || c3 || c4) {
        return c1 * c2 <= 0 && c3 * c4 <= 0;
    } else {
        return OnLineQ(a1, b1, b2) || OnLineQ(a2, b1, b2);
    }
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<vector<point> > lines(n, vector<point>(2));
        for (int i = 0; i < n; i++) {
            lines[i][0].input();
            lines[i][1].input();
        }
        Dsu dsu(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && CrossQ(lines[i][0], lines[i][1], lines[j][0],
                                     lines[j][1])) {
                    dsu.unit(i, j);
                }
            }
        }
        int a, b;
        while (cin >> a >> b && !(a == 0 && b == 0)) {
            if (dsu.find(a - 1) == dsu.find(b - 1)) {
                cout << "CONNECTED\n";
            } else {
                cout << "NOT CONNECTED\n";
            }
        }
    }
}