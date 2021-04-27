// Corn Fields

#include <cstdio>
const int MAX_M = 12;
const int MAX_N = 12;
const int MOD = 1e9;
int Dp[MAX_M][1 << MAX_N];
int Field[MAX_M];
int M, N;
void dfs(int m, int n, int s, int field, int ldp) {
    if (n == N) {
        Dp[m][s] = (Dp[m][s] + ldp) % MOD;
        return;
    }
    dfs(m, n + 1, s, field, ldp);
    if (!(field & (1 << n))) {
        dfs(m, n + 1, s | 1 << n, field | (1 << (n + 1)), ldp);
    }
}
int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0, x; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &x);
            Field[i] |= (!x) << j;
        }
    }
    dfs(0, 0, 0, Field[0], 1);
    for (int i = 1; i < M; i++) {
        for (int j = 0; j < (1 << N); j++) {
            dfs(i, 0, 0, Field[i] | j, Dp[i - 1][j]);
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << N); i++) {
        ans = (ans + Dp[M - 1][i]) % MOD;
    }
    printf("%d\n", ans);
}