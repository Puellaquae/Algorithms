// Combinations
#include <iostream>
#include <vector>
using namespace std;
const int MAX_N = 50000 + 5;
vector<bool> Primes(MAX_N, true);
int FactorCount(int n, int v) {
    int ans = 0;
    int rep = n;
    for (; rep != 0; rep /= v, ans += rep)
        ;
    return ans;
}
int ComFactor(int n, int m) {
    vector<int> res(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (Primes[i])
            res[i] = FactorCount(n, i);
    }
    for (int i = 2; i <= m; i++) {
        if (Primes[i])
            res[i] -= FactorCount(m, i);
    }
    for (int i = 2; i <= n - m; i++) {
        if (Primes[i])
            res[i] -= FactorCount(n - m, i);
    }
    int ans = 0;
    for (int i = 2; i < n + 1; i++) {
        if (res[i] > 0)
            ans++;
    }
    return ans;
}

int main() {
    Primes[1] = false;
    for (int i = 2; i < MAX_N; i++) {
        if (Primes[i] == false)
            continue;
        for (int k = 2; i * k < MAX_N; k++) {
            Primes[i * k] = false;
        }
    }
    int M, N;
    while (cin >> N >> M) {
        cout << ComFactor(N, M) << endl;
    }
    return 0;
}