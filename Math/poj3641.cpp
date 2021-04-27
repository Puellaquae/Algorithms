// Pseudoprime numbers 

#include <iostream>
using namespace std;
typedef long long int64;
int64 mpow(int64 x, int64 n, int64 mod) {
    int64 res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int64 isprime(int64 n) {
    if (n < 2)
        return 0;
    for (int64 i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int64 p, a;
    while (cin >> p >> a && p && a) {
        if (!isprime(p)&&mpow(a, p, p) == a % p) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    return 0;
}