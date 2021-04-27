// Let it Bead

#include <iostream>
#include <set>
#include <vector>
using namespace std;

typedef long long i64;

i64 power(i64 p, i64 n) {
    i64 sum = 1;
    while (n) {
        if (n & 1)
            sum *= p;
        p *= p;
        n /= 2;
    }
    return sum;
}

vector<int> divisor(const int &n) {
    vector<int> res;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}

set<int> prime_factor(int n) {
    set<int> res;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            res.insert(i);
            n /= i;
        }
    }
    if (n != 1) {
        res.insert(n);
    }
    return res;
}

i64 polya(const int &m, const int &n) {
    set<int> primes = prime_factor(n);
    vector<int> divs = divisor(n);
    i64 res = 0;
    for (size_t i = 0; i < divs.size(); i++) {
        i64 euler = divs[i];
        for (set<int>::iterator it = primes.begin(); it != primes.end(); it++) {
            int p = *it;
            if (divs[i] % p == 0)
                euler = euler / p * (p - 1);
        }
        res += euler * power(m, n / divs[i]);
    }
    res /= n;
    return res;
}

int main() {
    int c, s;
    while (~scanf("%d%d", &c, &s) && c && s) {
        if (s == 0) {
            puts("0");
            continue;
        }
        i64 count = polya(c, s) * s;
        if (s & 1)
            count += s * power(c, s / 2 + 1);
        else
            count += (power(c, s / 2 + 1) + power(c, s / 2)) * (s / 2);
        count /= 2 * s;
        printf("%lld\n", count);
    }
    return 0;
}