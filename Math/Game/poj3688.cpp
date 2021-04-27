// Cheat in the Game

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int A[10000 + 16];
bool dp[100000 + 16][2];

int main() {
    int N, M;
    while (cin >> N >> M, N) {
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        sort(A, A + N);
        memset(dp, 0, sizeof(dp));
        dp[A[0]][1] = true;
        for (int i = 1; i < N; i++) {
            for (int j = M; j > A[i]; j--) {
                if (dp[j - A[i]][0])
                    dp[j][1] = true;
                if (dp[j - A[i]][1])
                    dp[j][0] = true;
            }
            dp[A[i]][1] = true;
        }
        int ans = 0;
        for (int i = 1; i < M + 1; i++) {
            if (dp[i][1] && !dp[i][0])
                ++ans;
        }
        cout << ans << endl;
    }
    return 0;
}