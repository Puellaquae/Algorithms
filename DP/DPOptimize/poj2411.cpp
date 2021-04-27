// Mondriaan's Dream
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long i64;
const int MAX_M = 12;
int n, m;
i64 dp[2][1 << MAX_M];
void solve() {
    i64 *crt = dp[0], *next = dp[1];
    crt[0] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            for (int used = 0; used < 1 << m; used++) {
                if (used >> j & 1) {
                    next[used] = crt[used & ~(1 << j)];
                } else {
                    i64 res = 0;
                    if (j + 1 < m && !(used >> (j + 1) & 1)) {
                        res += crt[used | 1 << (j + 1)];
                    }
                    if (i + 1 < n) {
                        res += crt[used | 1 << j];
                    }
                    next[used] = res;
                }
            }
            swap(crt, next);
        }
    }
    printf("%lld\n", crt[0]);
}
int main() {
    while (~scanf("%d%d", &n, &m) && n && m) {
        memset(dp, 0, sizeof(dp));
        solve();
    }
}