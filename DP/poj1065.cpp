// Wooden Sticks
// Using DP
#include <algorithm>
#include <iostream>
#include <vector>

struct Stick {
    int L, W;
};
using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<Stick> Sticks(N);
    for (int i = 0; i < N; i++) {
        cin >> Sticks[i].L >> Sticks[i].W;
    }
    vector<int> DP(N);
    for (int i = 0; i < N; i++) {
        DP[i] = 1;
        for (int j = 0; j < i; j++) {
            if (Sticks[j].L <= Sticks[i].L && Sticks[j].W <= Sticks[i].W) {
                DP[i] = max(DP[i], DP[j] + 1);
            }
        }
    }
    cout << *max_element(DP.begin(),DP.end()) << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}