// GCD & LCM Inverse

#include <cmath>
#include <ctime>
#include <iostream>

typedef long long int64;

int64 GCD(int64 a, int64 b) {
    if (b == 0) {
        return a;
    } else {
        return GCD(b, a % b);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
    int64 gcd, lcm;
    while (std::cin >> gcd >> lcm) {
        for (int64 k = (int64)sqrt(lcm / gcd); k > 0; k--) {
            if ((lcm / gcd) % k == 0) {
                int64 j = lcm / gcd / k;
                if (GCD(j, k) == 1) {
                    std::cout << k * gcd << " " << j * gcd << '\n';
                    break;
                }
            }
        }
    }
    return 0;
}