// Counting Divisors

#include <iostream>
using namespace std;
typedef long long int64;
const int MAX_N = 1e6;
const int64 MOD = 998244353;
int64 Primes[MAX_N + 15];
int pos = 0;
bool Mark[MAX_N + 15];
int64 Ans[MAX_N + 15];
int64 Num[MAX_N + 15];
int64 solve(int64 l, int64 r, int64 k) {
    int n = r - l + 1;
    for (int i = 1; i <= n; i++) {
        Num[i] = l + i - 1;
        Ans[i] = 1;
    }
    for (int i = 0; i < pos && Primes[i] * Primes[i] <= r; i++) {
        int64 p = Primes[i];
        int64 t = ((l + p - 1) / p) * p;
        for (int j = t - l + 1; j <= n; j += p) {
            int64 num = 0;
            while (Num[j] % p == 0) {
                Num[j] /= p;
                num++;
            }
            Ans[j] = Ans[j] * (k * num % MOD + 1) % MOD;
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (Num[i] > 1) {
            Ans[i] = Ans[i] * (k + 1) % MOD;
        }
        res = (res + Ans[i]) % MOD;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    for (int i = 2; i <= MAX_N; i++) {
        if (!Mark[i]) {
            Mark[i] = Primes[pos++] = i;
        }
        for (int j = 0; j < pos && Primes[j] * i <= MAX_N; j++) {
            Mark[i * Primes[j]] = Primes[j];
            if (i % Primes[j] == 0) {
                break;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int64 l, r, k;
        cin >> l >> r >> k;
        cout << solve(l, r, k) << '\n';
    }
}