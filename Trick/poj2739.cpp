// Sum of Consecutive Prime Numbers
#include <iostream>
#include <vector>
using namespace std;
const int MAX_N = 2e5 + 15;
bool Mark[MAX_N];
vector<int> Primes;
int PPrime[MAX_N];
int main() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!Mark[i]) {
            Primes.push_back(i);
            Mark[i] = (bool)i;
        }
        for (int j = 0; j < (int)Primes.size() && Primes[j] * i <= MAX_N; j++) {
            Mark[i * Primes[j]] = Primes[j];
            if (i % Primes[j] == 0) {
                break;
            }
        }
    }
    int pos = Primes.size();
    PPrime[0] = 0;
    for (int i = 0; i < pos; i++) {
        PPrime[i + 1] = PPrime[i] + Primes[i];
    }
    int x;
    while (cin >> x && x) {
        int l = 0, r = 1, sum, ans = 0;
        while (r <= pos && Primes[r - 1] <= x) {
            sum = PPrime[r] - PPrime[l];
            if (sum < x) {
                r++;
            } else if (sum > x) {
                l++;
            } else {
                ans++;
                r++;
            }
            if (l == r) {
                r++;
            }
        }
        cout << ans << '\n';
    }
}