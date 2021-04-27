#include <vector>
#include <iostream>

void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

const int INF = 0x3f3f3f3f;

int main() {
    optimize_cpp_stdio();
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, INF));
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;
    while (m--) {
        int k;
        std::cin >> k;
        std::vector<int> nodes(k);
        for (int i = 0; i < k; i++) {
            std::cin >> nodes[i];
            --nodes[i];
            for (int j = 0; j < i; j++) {
                dp[nodes[i]][nodes[j]] = 1;
                dp[nodes[j]][nodes[i]] = 1;
            }
        }
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dp[i][k] + dp[k][j] < dp[i][j])
                    dp[i][j] = dp[i][k] + dp[k][j];
    int ans = INF;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += dp[i][j];
        ans = std::min(ans, sum * 100 / (n - 1));
    }
    std::cout << ans << "\n";
    return 0;
}