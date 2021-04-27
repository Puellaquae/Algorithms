// Easy Problem

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int w[100050];
long long dp[100050][5];
const char h[] = "hard";
int main() {
    int n;
    string s;
    scanf("%d", &n);
    cin >> s;
    for (int i = 0; i < n; i++) {
        scanf("%d", w + i);
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            dp[i + 1][j + (s[i] == h[j])] =
                min(dp[i + 1][j + (s[i] == h[j])], dp[i][j]);
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + w[i]);
        }
    }
    cout << *min_element(dp[n], dp[n] + 4) << endl;
}