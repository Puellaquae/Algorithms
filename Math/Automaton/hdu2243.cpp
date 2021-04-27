// 考研路茫茫——单词情结

#include <cstdio>
#include <cstring>
#include <queue>
const int MAXN = 50;
using namespace std;
typedef unsigned long long ll;
int N, M;
char St[MAXN];

struct Marix {
    //矩阵
    ll mo[MAXN][MAXN], n;
    Marix(){};

    explicit Marix(const int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mo[i][j] = 0;
            }
        }
    }
};

Marix Mul(Marix a, Marix b) {
    Marix res = Marix(a.n);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.n; j++) {
            for (int k = 0; k < a.n; k++) {
                res.mo[i][j] = res.mo[i][j] + a.mo[i][k] * b.mo[k][j];
            }
        }
    }
    return res;
}

Marix PowMod(Marix a, ll n) {
    Marix res = Marix(a.n);
    for (int i = 0; i < a.n; i++) {
        res.mo[i][i] = 1;
    }
    while (n) {
        if (n & 1)
            res = Mul(res, a);
        a = Mul(a, a);
        n >>= 1;
    }
    return res;
}

struct Trie {
    int next[MAXN][26], fail[MAXN], End[MAXN], root, id;

    int newnode() {
        for (int i = 0; i < 26; i++) {
            next[id][i] = -1;
        }
        End[id] = 0;
        return id++;
    }

    void init() {
        id = 0;
        root = newnode();
    }

    void Insert(char *str) {
        const int len = strlen(str);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (next[now][str[i] - 'a'] == -1) {
                next[now][str[i] - 'a'] = newnode();
            }
            now = next[now][str[i] - 'a'];
        }
        End[now] = 1;
    }

    void build() {
        queue<int> que;
        for (int i = 0; i < 26; i++) {
            if (next[root][i] == -1) {
                next[root][i] = root;
            } else {
                fail[next[root][i]] = root;
                que.push(next[root][i]);
            }
        }
        while (!que.empty()) {
            const int now = que.front();
            que.pop();
            for (int i = 0; i < 26; i++) {
                if (next[now][i] == -1) {
                    next[now][i] = next[fail[now]][i];
                } else {
                    fail[next[now][i]] = next[fail[now]][i];
                    que.push(next[now][i]);
                }
            }
            End[now] |= End[fail[now]];
        }
    }

    Marix get_marix() {
        Marix res = Marix(id + 1);
        for (int i = 0; i < id; i++) {
            for (int j = 0; j < 26; j++) {
                if (End[next[i][j]])
                    continue;
                res.mo[i][next[i][j]]++;
            }
        }
        for (int i = 0; i < id + 1; i++) {
            res.mo[i][id] = 1;
        }
        return res;
    }
} Ac;

int main() {
    while (~scanf("%d%d", &N, &M)) {
        Ac.init();
        for (int i = 0; i < N; i++) {
            scanf("%s", St);
            Ac.Insert(St);
        }
        Ac.build();
        Marix Mar1 = Ac.get_marix();
        ll res = 0;
        Mar1 = PowMod(Mar1, M);
        for (int i = 0; i < Mar1.n; i++) {
            res += Mar1.mo[0][i];
        }
        res--;
        Marix mar2 = Marix(2);
        mar2.mo[0][0] = 26;
        mar2.mo[1][1] = mar2.mo[0][1] = 1;
        mar2 = PowMod(mar2, M);
        ll ans = mar2.mo[0][0] + mar2.mo[0][1];
        ans--;
        ans -= res;
        printf("%I64u\n", ans);
    }
}
