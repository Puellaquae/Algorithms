// 分手是祝愿

#include <cstdio>
using namespace std;
typedef long long ll;
ll p = 100003;
ll fp(ll a, ll b) {
    ll s = 1;
    while (b) {
        if (b & 1)
            s = s * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return s;
}
int a[100010];
ll f[100010];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int i, j;
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int num = 0;
    for (i = n; i >= 1; i--)
        if (a[i]) {
            num++;
            for (j = 1; j * j <= i; j++)
                if (i % j == 0) {
                    a[j] ^= 1;
                    if (j * j != i)
                        a[i / j] ^= 1;
                }
        }
    ll s = 1;
    f[n + 1] = 1;
    for (i = n; i >= 1; i--)
        f[i] = (n + (n - i) * f[i + 1] % p) % p * fp(i, p - 2) % p;
    if (num <= k)
        s = num;
    else {
        s = 0;
        for (i = num; i > k; i--)
            s = (s + f[i]) % p;
        s = (s + k) % p;
    }
    for (i = 1; i <= n; i++)
        s = s * i % p;
    printf("%lld\n", s);
    return 0;
}