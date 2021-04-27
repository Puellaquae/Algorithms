// Arrange the Bulls

#include <iostream>
using namespace std;
const int MAX_N = 20;
const int MAX_M = 20;
int dp[1 << MAX_M];
bool like[MAX_N][MAX_M];

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int P;
        cin >> P;
        for (int j = 0; j < P; j++) {
            int b;
            cin >> b;
            like[i][b - 1] = true;
        }
    }
    for (int i = 0; i < M; i++) {
        if (like[0][i]) {
            dp[1 << i] = 1;
        }
    }
    for (int i = 1; i < N; ++i) {
        for (int comb = (1 << i) - 1, x, y; comb < (1 << M); x = comb & -comb,
                 y = comb + x, comb = ((comb & ~y) / x >> 1) | y) {
            if (dp[comb]) {
                for (int j = 0; j < M; ++j) {
                    if (like[i][j] && !((comb >> j) & 1)) {
                        dp[comb | (1 << j)] += dp[comb];
                    }
                }
            }
        }
    }

    int result = 0;
    for (int bit = 0; bit < (1 << M); bit++) {
        int cnt = 0;
        for (int j = 0; j < M; j++) {
            if (bit & 1 << j)
                cnt++;
        }
        if (cnt == N) {
            result += dp[bit];
        }
    }
    cout << result << endl;
    return 0;
}