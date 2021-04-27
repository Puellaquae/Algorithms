// 游戏

#include <iostream>
#include <vector>
using i64 = long long;
using namespace std;
constexpr i64 MOD = 1000000000 + 7;

auto QPow(i64 a, i64 b) {
    i64 res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
    }
    return res;
}

int main() {
    i64 l, r, cnt = 0, ans = 0;
    cin >> l >> r;
    const i64 n = r - l + 1;
    vector<bool> vis(r + 1, false);
    for (int i = l; i <= r; ++i) {
        if (!vis[i]) {
            ++cnt;
            for (int j = i + i; j <= r; j += i) {
                vis[j] = true;
            }
        }
    }
    vector<i64> fac(n + 1), inv(n + 1);
    fac[0] = fac[1] = 1;
    for (i64 i = 2; i <= n; i++) {
        fac[i] = 1ll * fac[i - 1] * i % MOD;
    }
    inv[n] = QPow(fac[n], MOD - 2);
    for (i64 i = n - 1; i >= 0; i--) {
        inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
    }
    auto C = [&fac,&inv](const i64 n, const i64 m) {
        return 1ll * fac[n] * inv[m] % MOD * inv[n - m] %
                MOD;
    };
    for (i64 i = cnt; i <= n; i++) {
        const i64 add = 1ll * i % MOD * C(i - 1, cnt - 1) % MOD;
        ans = (ans + add) % MOD;
    }
    cout << ans * fac[cnt] % MOD * fac[n - cnt] % MOD;
    return 0;
}