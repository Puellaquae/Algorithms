// Necklace
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 20;
long long dp[(1 << 18)][MAXN];
bool G[MAXN][MAXN];

int main() {
    int N, M;
    while (scanf("%d%d", &N, &M) != EOF) {
        memset(G, false, sizeof G);
        for (int i = 0, u, v; i < M; i++) {
            scanf("%d%d", &u, &v);
            G[u][v] = G[v][u] = true;
        }
        memset(dp, 0, sizeof dp);
        dp[1][1] = 1;
        for (int i = 0; i < (1 << N); i++) {
            for (int j = N; j > 0; j--) {
                if (dp[i][j]) {
                    for (int k = 1; k <= N; k++) {
                        if (G[k][j] && !(i & (1 << (k - 1)))) {
                            dp[i | 1 << (k - 1)][k] += dp[i][j];
                        }
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 1; i <= N; i++) {
            if (G[1][i])
                ans += dp[(1 << N) - 1][i];
        }
        printf("%lld\n", ans);
    }
}