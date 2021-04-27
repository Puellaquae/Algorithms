// Trisection Crystallization

#include <cstdio>
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        double v, u, ans = 0.0;
        scanf("%lf%lf", &v, &u);
        if (u + u >= v) {
            ans = 1.0 - 3.0 * (v - u) * (v - u) / (v * v);
        } else {
            ans = (3.0 * u - v) * (3.0 * u - v) / (v * v);
        }
        printf("%.9f\n", ans);
    }
}