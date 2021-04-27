// Nim

#include <cstring>
#include <iostream>
using namespace std;
int dp[40][20000];
int m[40];
int n;
int dfs(int id, int s) {
    if (dp[id][s] != -1) {
        return dp[id][s];
    }
    if (s <= 0) {
        dp[id][s] = 1;
        return 1;
    }
    for (int i = 1; i <= m[id] && i <= s; i++) {
        if (dfs((id + 1) % (2 * n), s - i) == 0) {
            dp[id][s] = 1;
            return 1;
        }
    }
    dp[id][s] = 0;
    return 0;
}

int main() {
    int s;
    while (cin >> n && n != 0) {
        cin >> s;
        for (int i = 0; i < 2 * n; i++) {
            cin >> m[i];
        }
        memset(dp, -1, sizeof dp);
        cout << dfs(0, s) << endl;
    }
}