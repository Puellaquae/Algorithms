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
int main() {
    int64 n;
    cin >> n;
    cout << mpow(n, n, 10) << endl;
}