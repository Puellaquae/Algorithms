//机器人的项链

#include <iostream>
#include <math.h>
using namespace std;
#define M 66000
typedef long long i64;

int prime[6600], k, vis[M] = {0}, mod = 9937;

int Euler(int n) {
    int i, res = n;
    for (i = 0; i < k && (i64)prime[i] * prime[i] <= n; i++) {
        if (n % prime[i] == 0) {
            do
                n /= prime[i];
            while (n % prime[i] == 0);
            res = res - res / prime[i];
        }
    }
    if (n > 1)
        res = res - res / n;
    return res % mod;
}

int qmod(int a, int b) {
    a %= mod;
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

int main() {
    int n, m, i, j, ms, ans;
    k = 0;
    for (i = 2; i < M; i++) {
        if (!vis[i]) {
            prime[k++] = i;
            for (j = i + i; j < M; j += i)
                vis[j] = 1;
        }
    }
    while (~scanf("%d%d", &n, &m)) {
        ms = (int)sqrt(n + 0.5);
        ans = 0;
        for (i = 1; i <= ms; i++) {
            if (n % i == 0) {
                ans = (ans + Euler(n / i) * qmod(m, i) % mod) % mod;
                if (i != n / i)
                    ans = (ans + Euler(i) * qmod(m, n / i) % mod) % mod;
            }
        }
        int tot = ans;
        for (ans = 0; ans < mod; ans++)
            if ((i64)ans * n % mod == tot % mod)
                break;
        printf("%d\n", ans);
    }
    return 0;
}