const int MAX_N = 55;
const int MAX_STATE = 1005;
const int MAX_LEN_S = 1005;
const int INF = 0x3f3f3f3f;

const char AGCT[] = "AGCT";
int N;
#include <string>
std::string S, P[MAX_N];
int next[MAX_STATE][4];
// DNA repair

bool ng[MAX_STATE];
int dp[MAX_LEN_S + 1][MAX_STATE];

#include <algorithm>
#include <cstring>
#include <vector>
int solve() {
    std::vector<std::string> pfx;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= P[i].size(); j++) {
            pfx.push_back(P[i].substr(0, j));
        }
    }
    std::sort(pfx.begin(), pfx.end());
    pfx.erase(std::unique(pfx.begin(), pfx.end()), pfx.end());
    int K = pfx.size();
    for (int i = 0; i < K; i++) {
        ng[i] = false;
        for (int j = 0; j < N; j++) {
            ng[i] |=
                P[j].size() <= pfx[i].size() &&
                pfx[i].substr(pfx[i].size() - P[j].size(), P[j].size()) == P[j];
        }
        for (int j = 0; j < 4; j++) {
            std::string s = pfx[i] + AGCT[j];
            int k;
            for (;;) {
                k = std::lower_bound(pfx.begin(), pfx.end(), s) - pfx.begin();
                if (k < K && pfx[k] == s)
                    break;
                s = s.substr(1);
            }
            next[i][j] = k;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i < K; i++)
        dp[0][i] = 0;
    for (int t = 0; t < S.size(); t++) {
        for (int i = 0; i < K; i++)
            dp[t + 1][i] = INF;
        for (int i = 0; i < K; i++) {
            if (ng[i])
                continue;
            for (int j = 0; j < 4; j++) {
                int k = next[i][j];
                dp[t + 1][k] = std::min(dp[t + 1][k],
                                        dp[t][i] + (S[t] == AGCT[j] ? 0 : 1));
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < K; i++) {
        if (ng[i])
            continue;
        ans = std::min(ans, dp[S.size()][i]);
    }
    if (ans == INF)
        return -1;
    else
        return ans;
}
#include <iostream>
int main() {
    int t = 0;
    while (std::cin >> N, N) {
        for (int i = 0; i < N; i++) {
            std::cin >> P[i];
        }
        std::cin >> S;
        std::cout << "Case " << ++t << ": " << solve() << std::endl;
    }
}