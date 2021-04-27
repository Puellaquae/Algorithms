// 病毒侵袭

#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 1e5 + 6;

namespace AC
{
    int Tr[N][128], Tot = 0, PIdx = 0;
    queue<int> Q;
    int E[N], Fail[N];

    void Insert(const char *s) {
        int u = 0;
        for (int i = 1; s[i]; i++) {
            if (!Tr[u][s[i]])
                Tr[u][s[i]] = ++Tot;
            u = Tr[u][s[i]];
        }
        E[u] = ++PIdx;
    }

    void Build() {
        for (int i = 0; i < 128; i++)
            if (Tr[0][i])
                Q.push(Tr[0][i]);
        while (!Q.empty()) {
            const int u = Q.front();
            Q.pop();
            for (int i = 0; i < 128; i++) {
                if (Tr[u][i])
                    Fail[Tr[u][i]] = Tr[Fail[u]][i], Q.push(Tr[u][i]);
                else
                    Tr[u][i] = Tr[Fail[u]][i];
            }
        }
    }

    int Ans[4];

    int Query(const char *t) {
        int u = 0, res = 0;
        for (int i = 1; t[i]; i++) {
            u = Tr[u][t[i]]; // 转移
            for (int j = u; j && E[j] != -1; j = Fail[j]) {
                if (E[j])
                    Ans[res++] = E[j]; //, E[j] = -1;
            }
        }
        sort(Ans, Ans + res);
        return res;
    }
} // namespace AC

char S[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", S + 1), AC::Insert(S);
    AC::Build();
    int m;
    scanf("%d", &m);
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%s", S + 1);
        const int res = AC::Query(S);
        if (res) {
            tot++;
            printf("web %d: ", i);
            for (int j = 0; j < res; j++) {
                printf("%d%c", AC::Ans[j], j < res - 1 ? ' ' : '\n');
            }
        }
    }
    printf("total: %d\n", tot);
    return 0;
}