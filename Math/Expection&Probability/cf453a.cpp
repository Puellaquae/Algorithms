// Little Pony and Expected Maximum

#include <cmath>
#include <cstdio>

int main() {
    int n, m;
    while (~scanf("%d%d", &m, &n)) {
        double ans = 0;
        for (int i = 1; i < m; i++)
            ans += pow(static_cast<double>(i) / m, n);
        printf("%.12lf\n", static_cast<double>(m) - ans);
    }
}