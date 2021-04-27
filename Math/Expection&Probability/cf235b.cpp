// Let's Play Osu!

#include <cstdio>
int main() {
    int n;
    double a, f1 = 0.0, f2 = 0.0;
    scanf("%d", &n);
    while (~scanf("%lf", &a)) {
        f2 += f1 * 2.0 * a + a;
        f1 = f1 * a + a;
    }
    printf("%.15f", f2);
    return 0;
}