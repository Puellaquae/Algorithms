// Graveyard Design
#include <iostream>
#include <vector>
struct Ans {
    int l, r;
};
using namespace std;
typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long uint64;
const int P_LENGTH = 1e7 + 10;
const uint64 MAX_UINT64 = 0xffffffffffffffff;
uint64 P[P_LENGTH];
int main() {
    P[0] = 0;
    for (int i = 1; i <= P_LENGTH; i++) {
        P[i] = P[i - 1] + i * i;
    }
    uint64 n;
    cin >> n;
    int l = 0, r = 1;
    uint64 sum;
    vector<Ans> ans;
    while (r <= P_LENGTH && 1ULL * r * r <= n) {
        sum = P[r] - P[l];
        if (sum < n) {
            r++;
        } else if (sum > n) {
            l++;
        } else {
            ans.push_back({l, r});
            r++;
        }
        if (l == r) {
            r++;
        }
    }
    cout << ans.size() << "\n";
    for (uint i = 0; i < ans.size(); i++) {
        cout << ans[i].l - ans[i].r + 1;
        for (int l = ans[i].l; l <= ans[i].r; l++) {
            cout << " " << l;
        }
    }
}