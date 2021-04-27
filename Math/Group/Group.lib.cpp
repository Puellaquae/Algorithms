#include <vector>
#include <map>
using std::vector;
using std::map;
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

//************************************
// Method:    divisor
// FullName:  divisor
// Access:    public
// Returns:   vector<int> 约数
// Qualifier: 约数枚举
// Parameter: const int & n 目标数n
//************************************
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

//************************************
// Method:    prime_factor
// FullName:  prime_factor
// Access:    public
// Returns:   map<int, int> 
// Note: Key:Factor Value:Times
// Sample: 12 : {2:2,3:1}
// Qualifier: 整数分解
// Parameter: int n
//************************************
map<int, int> prime_factor(int n) {
    map<int, int> res;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            ++res[i];
            n /= i;
        }
    }
    if (n != 1) {
        res[n] = 1;
    }
    return res;
}

i64 euler(int n) {
    i64 euler = n;
    set<int> primes = prime_factor(n);
    for (set<int>::iterator it = primes.begin(); it != primes.end(); it++) {
        euler = euler / *it * (*it - 1)；
    }
    return euler;
}

i64 polya(int m, int n) {
    map<int, int> primes = prime_factor(n);
    vector<int> divs = divisor(n);
    i64 res = 0;
    for (int i = 0; i < divs.size(); ++i) {
        // 求divs[i]的欧拉函数值
        i64 euler = divs[i];
        for (map<int, int>::iterator it = primes.begin(); it != primes.end();
             ++it) {
            int p = it->first;
            if (divs[i] % p == 0)
                euler = euler / p * (p - 1);
        }

        res += euler * power(m, n / divs[i]);
    }

    // 最后除以n
    res /= n;
    return res;
}