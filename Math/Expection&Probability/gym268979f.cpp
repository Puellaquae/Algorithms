// Problem Solving Monster

#include <iostream>
using namespace std;
using i64 = long long;
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    i64 r, s, m;
    while (t--) {
        cin >> r >> s >> m;
        if (2 * r <= s) {
            cout << "1\n";
            continue;
        }
        i64 p = r * QPow(s, MOD - 2) % MOD;
        p = (1 - p + MOD) * QPow(p, MOD - 2) % MOD;
        cout << QPow(p, m) << endl;
    }
    return 0;
}