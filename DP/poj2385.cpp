// Apple Catching
// Using DP
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T, W;
    cin >> T >> W;
    vector<int> Fall(T + 1);
    for (int i = 1; i <= T; i++) {
        cin >> Fall[i];
    }
    vector<vector<int> > dp(T + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= T; ++i) {
        dp[i][0] = dp[i - 1][0] + 2 - Fall[i];
        for (int j = 1; j <= W; ++j) {
            if (j % 2 != 0)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + Fall[i] - 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + 2 - Fall[i];
        }
    }
    cout << dp[T][W] << endl;
}