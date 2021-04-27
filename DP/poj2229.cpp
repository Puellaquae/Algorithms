// Sumsets
// Using DP
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> dp(N + 1);
    dp[1] = 1, dp[2] = 2;
    for (int i = 3; i <= N; i++)
        dp[i] = (i % 2 != 0 ? dp[i - 1] : (dp[i - 2] + dp[i / 2]) % 1000000000);
    cout << dp[N] << endl;
    return 0;
}