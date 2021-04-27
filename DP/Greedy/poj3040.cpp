// Allowance
// Using Greedy
#include <algorithm>
#include <iostream>
#include <vector>

struct Coin {
    int V, B;
};

bool cmp(Coin a, Coin b) { return a.V > b.V; }

using namespace std;
int main() {
    int N, C;
    cin >> N >> C;
    vector<Coin> Coins(N);
    for (int i = 0; i < N; i++) {
        cin >> Coins[i].V >> Coins[i].B;
    }
    sort(Coins.begin(), Coins.end(), cmp);
    int ans=0;
    while (true) {
        vector<int> Use(N);
        int rest = C;
        for (int i = 0; i < N; i++) {
            Use[i] = min(rest / Coins[i].V, Coins[i].B);
            rest -= Coins[i].V * Use[i];
        }
        if (rest) {
            for (int i = N - 1; i >= 0; i--)
                if (Coins[i].B && Coins[i].V >= rest) {
                    Use[i]++;
                    rest = 0;
                    break;
                }
        }
        if (rest)
            break;
        int MinCanPay = 2e9;
        for (int i = 0; i < N; i++) {
            if (Use[i])
                MinCanPay = min(Coins[i].B / Use[i], MinCanPay);
        }
        ans += MinCanPay;
        for (int i = 0; i < N; i++) {
            if (Use[i]) {
                Coins[i].B -= Use[i] * MinCanPay;
            }
        }
    }
    std::cout << ans << endl;
}