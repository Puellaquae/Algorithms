// 病毒侵袭持续中

#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
const int N = 5e4 + 6;

namespace AC
{
    int Tr[N][128], Tot = 0, PIdx = 0;
    queue<int> Q;
    int E[N], Fail[N];

    void Init() {
        memset(Tr, 0, sizeof Tr);
        memset(E, 0, sizeof E);
        memset(Fail, 0, sizeof Fail);
        Tot = 0;
        PIdx = 0;
        Q = queue<int>();
    }

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

    int Ans[1005];

    int Query(const char *t) {
        memset(Ans, 0, sizeof Ans);
        int u = 0, res = 0;
        for (int i = 1; t[i]; i++) {
            u = Tr[u][t[i]]; // 转移
            for (int j = u; j && E[j] != -1; j = Fail[j]) {
                if (E[j])
                    res++, Ans[E[j]]++; //, E[j] = -1;
            }
        }
        return res;
    }
} // namespace AC

char P[1005][55];
char S[2000050];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        AC::Init();
        for (int i = 1; i <= n; i++)
            scanf("%s", P[i] + 1), AC::Insert(P[i]);
        AC::Build();
        int m;
        scanf("%d", &m);
        scanf("%s", S + 1);
        AC::Query(S);
        for (int i = 1; i <= n; i++) {
            if (AC::Ans[i]) {
                printf("%s: %d\n", P[i] + 1, AC::Ans[i]);
            }
        }
    }
    return 0;
}
