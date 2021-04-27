// Bloodsucker

#include <cstdio>
double dp[100005];
int main() {
    int T, n, i;
    double p, nlf, ilf, s1, s2, p1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lf", &n, &p);
        dp[n] = 0.0;
        nlf = n;
        for (i = n - 1; i >= 1; i--) {
            ilf = i;
            s1 = nlf * (nlf - 1.0) / 2.0;
            s2 = ilf * (nlf - ilf);
            p1 = s2 / s1 * p;
            dp[i] = (dp[i + 1] * p1 + 1) / p1;
        }
        printf("%.3f\n", dp[1]);
    }
    return 0;
}