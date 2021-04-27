// AB Ring

#include <cstdio>
int main() {
    int t, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &a, &b);
        if (a + b <= 1) {
            printf("0.000000000\n");
        } else {
            double ans = 2.0 * a * b / (a + b - 1.0);
            printf("%.9lf\n", ans);
        }
    }
}