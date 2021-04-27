// The Oculus

#include <cstdio>
typedef unsigned long long ull;
typedef long long ll;
const int maxn = 2e6 + 7;

int a[maxn];
ull f[maxn];

void init() {
    f[1] = 1;
    f[2] = 2;
    for (int i = 3; i < maxn; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        ull s1 = 0, s2 = 0, s3 = 0;
        int m1;
        scanf("%d", &m1);
        for (int i = 1; i <= m1; i++) {
            int x;
            scanf("%d", &x);
            if (x)
                s1 += f[i];
        }
        int m2;
        scanf("%d", &m2);
        for (int i = 1; i <= m2; i++) {
            int x;
            scanf("%d", &x);
            if (x)
                s2 += f[i];
        }
        int m3;
        scanf("%d", &m3);
        for (int i = 1; i <= m3; i++) {
            scanf("%d", &a[i]);
            if (a[i])
                s3 += f[i];
        }
        ull s4 = s1 * s2;
        int ans = 0;
        for (int i = 1; i < m3; i++) {
            if (a[i] == 0 && a[i + 1] != 1 && a[i - 1] != 1) {
                if (s3 + f[i] == s4) {
                    ans = i;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}