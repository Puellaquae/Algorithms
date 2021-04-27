// Keywords Search

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e6 + 6;

namespace AC {
int tr[N][26], tot;
queue<int> q;
int e[N], fail[N];
void init() {
    memset(tr, 0, sizeof tr);
    memset(e, 0, sizeof e);
    memset(fail, 0, sizeof fail);
    tot = 0;
    q = queue<int>();
}
void insert(char *s) {
    int u = 0;
    for (int i = 1; s[i]; i++) {
        if (!tr[u][s[i] - 'a'])
            tr[u][s[i] - 'a'] = ++tot;
        u = tr[u][s[i] - 'a'];
    }
    e[u]++;
}
void build() {
    for (int i = 0; i < 26; i++)
        if (tr[0][i])
            q.push(tr[0][i]);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (tr[u][i])
                fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
            else
                tr[u][i] = tr[fail[u]][i];
        }
    }
}
int query(char *t) {
    int u = 0, res = 0;
    for (int i = 1; t[i]; i++) {
        u = tr[u][t[i] - 'a']; // 转移
        for (int j = u; j && e[j] != -1; j = fail[j]) {
            res += e[j], e[j] = -1;
        }
    }
    return res;
}
} // namespace AC

char s[N];
int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        AC::init();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%s", s + 1), AC::insert(s);
        scanf("%s", s + 1);
        AC::build();
        printf("%d\n", AC::query(s));
    }
    return 0;
}