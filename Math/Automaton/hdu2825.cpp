// Wireless Password

#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int BRANCH = 26;
const int MAX_M = 10;
const int MOD = 20090717;
const int NODE_PREP = 111;
int NodePoolESP, Trie[NODE_PREP][BRANCH], Fail[NODE_PREP], Flag[NODE_PREP];

void Insert(const char *s, const int k) {
    int x = 0;
    for (int i = 0; s[i]; i++) {
        const int y = s[i] - 'a';
        if (Trie[x][y] == 0)
            Trie[x][y] = ++NodePoolESP;
        x = Trie[x][y];
    }
    Flag[x] |= 1 << k;
}

void Init() {
    memset(Fail, 0, sizeof Fail);
    queue<int> que;
    for (int i = 0; i < BRANCH; i++) {
        if (Trie[0][i])
            que.push(Trie[0][i]);
    }
    while (!que.empty()) {
        const int x = que.front();
        que.pop();
        for (int i = 0; i < BRANCH; ++i) {
            if (Trie[x][i]) {
                que.push(Trie[x][i]);
                Fail[Trie[x][i]] = Trie[Fail[x]][i];
                Flag[Trie[x][i]] |= Flag[Trie[Fail[x]][i]];
            } else {
                Trie[x][i] = Trie[Fail[x]][i];
            }
        }
    }
}

int GetCnt(const int s) {
    int res = 0;
    for (int i = 0; i < MAX_M; ++i) {
        if ((s >> i) & 1)
            ++res;
    }
    return res;
}

int Dp[BRANCH][NODE_PREP][1 << MAX_M];

int main() {
    char str[255];
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k) && (n || m || k)) {
        NodePoolESP = 0;
        memset(Trie, 0, sizeof Trie);
        memset(Flag, 0, sizeof Flag);
        for (int i = 0; i < m; ++i) {
            scanf("%s", str);
            Insert(str, i);
        }
        Init();
        memset(Dp, 0, sizeof Dp);
        Dp[0][0][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= NodePoolESP; ++j) {
                for (int k1 = 0; k1 < (1 << m); ++k1) {
                    if (Dp[i][j][k1] == 0)
                        continue;
                    for (int y = 0; y < BRANCH; ++y) {
                        Dp[i + 1][Trie[j][y]][k1 | Flag[Trie[j][y]]] += Dp[i][j][k1];
                        Dp[i + 1][Trie[j][y]][k1 | Flag[Trie[j][y]]] %= MOD;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i <= NodePoolESP; ++i) {
            for (int j = 0; j < (1 << m); ++j) {
                if (GetCnt(j) < k)
                    continue;
                res += Dp[n][i][j];
                res %= MOD;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}