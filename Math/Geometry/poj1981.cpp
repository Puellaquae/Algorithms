// Circle and Points
#include <cmath>
#include <cstdio>
struct p {
    double x, y;
} ps[305];
double dist(p a, p b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &(ps[i].x), &(ps[i].y));
        }
        int ans = 1;
        const double eps = 1e-8;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dist(ps[i], ps[j]) > 2.0) {
                    continue;
                }
                int cnt1 = 2;
                p o1;
                double l = dist(ps[i], ps[j]);
                double s = sqrt(1 - l * l / 4.0);
                o1.x = (ps[i].x + ps[j].x) / 2.0 - s * (ps[i].y - ps[j].y) / l;
                o1.y = (ps[i].y + ps[j].y) / 2.0 + s * (ps[i].x - ps[j].x) / l;
                for (int k = 0; k < n; k++) {
                    if (k != i && k != j) {
                        if (dist(ps[k], o1) < 1.0 + eps) {
                            cnt1++;
                        }
                    }
                }
                ans = cnt1 > ans ? cnt1 : ans;
            }
        }
        printf("%d\n", ans);
    }
}