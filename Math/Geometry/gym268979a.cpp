// Cross River

#include <cstdio>
#define YES                                                                    \
    printf("YES %lld/%lld\n", x0 / gcd(x0, v0), v0 / gcd(x0, v0));             \
    continue
#define NO                                                                     \
    printf("NO\n");                                                            \
    continue
typedef long long i64;
i64 gcd(i64 a, i64 b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    i64 t, x0, y0, v0, v1, x[3], y[3];
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld%lld%lld", &x0, &y0, &v0, &v1);
        for (int i = 0; i < 3; i++) {
            scanf("%lld%lld", x + i, y + i);
        }
        bool ok1 = false, ok2 = false;
        for (int i = 0; i < 3; i++) {
            ok1 |= v0 * y[i] >= x[i] * v1;
            ok2 |= v0 * y[i] <= x[i] * v1;
        }
        if (v0 == 0) {
            if ((x0 != 0 || (ok1 && ok2)) || v1 == 0) {
                NO;
            } else {
                printf("YES %lld/%lld\n", y0 / gcd(y0, v1), v1 / gcd(y0, v1));
                continue;
            }
        }
        if (v0 * y0 > x0 * v1) {
            NO;
        }
        if (!(ok1 && ok2)) {
            YES;
        }
        double mmin = 0x7fffffff;
        i64 p = -1;
        for (int i = 0; i < 3; i++) {
            if (y[i] - 1. * v1 / v0 * x[i] < mmin) {
                mmin = y[i] - 1. * v1 / v0 * x[i];
                p = i;
            }
        }
        if (v0 * (y0 - y[p]) >= (x0 - x[p]) * v1) {
            NO;
        }
        YES;
    }
}