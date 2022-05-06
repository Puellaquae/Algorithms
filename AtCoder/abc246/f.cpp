#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

constexpr int64_t MOD = 998244353;
constexpr int N = 20;

int64_t mPow(int64_t x, int64_t n, int64_t mod) {
    int64_t res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n, l;
    cin >> n >> l;
    vector<bitset<26> > s(n, bitset<26>());
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        for (char& c : str) {
            s[i].set(c - 'a');
        }
    }
    int64_t res = 0;
    for (int i = 1; i < (1 << n); i++) {
        bitset<N> u(i);
        bitset<26> cs;
        cs.flip();
        for (int j = 0; j < n; j++) {
            if (u.test(j)) {
                cs &= s[j];
            }
        }
        int64_t p = mPow(cs.count(), l, MOD);
        if (u.count() % 2 == 0) {
            res += MOD - p;
        } else {
            res += p;
        }
        res %= MOD;
    }
    cout << res << endl;
}