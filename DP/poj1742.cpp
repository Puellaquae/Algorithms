// Coins
// Like Cash Machine
// Using DP 
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool L(int x){
    return x>=0;
}

int main() {
    int n, m;
    while (cin >> n >> m && n && m) {
        vector<int> a(n);
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        vector<int> dp(m + 1, -1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                if (dp[j] >= 0) {
                    dp[j] = c[i];
                } else if (j < a[i] || dp[j - a[i]] <= 0) {
                    dp[j] = -1;
                } else {
                    dp[j] = dp[j - a[i]] - 1;
                }
            }
        }
        //cout << count_if(dp.begin(), dp.end(), [&](int x) -> bool { return x >= 0; }) - 1 << endl;
        cout << count_if(dp.begin(), dp.end(), L) - 1 << endl;
    }
    return 0;
}