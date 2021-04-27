// Ant Counting
// Using DP
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int M = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int T, A, S, B;
    cin >> T >> A >> S >> B;
    vector<int> a(T, 0);
    for (int i = 0, x; i < A; i++) {
        cin >> x;
        a[x - 1]++;
    }
    int ans = 0;
    vector<vector<int> > dp(T + 1, vector<int>(A + 1));
    for (int i = 0; i <= T; i++) {
        dp[i][0] = 1;
    }
    for (int i = 0; i < T; i++) {
        for (int j = 1; j <= A; j++) {
            if (j - 1 - a[i] >= 0) {
                dp[i + 1][j] = (dp[i + 1][j - 1] + dp[i][j] - dp[i][j - 1 - a[i]] + M) % M;
            } else {
                dp[i + 1][j] = (dp[i + 1][j - 1] + dp[i][j]) % M;
            }
        }
    }
    for (int i = S; i <= B; i++) {
        ans = (ans + dp[T][i]) % M;
    }
    cout << ans << endl;
}