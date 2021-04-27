// Constellations

#include <cstdio>
typedef unsigned long long ull;
const int MAX_SIZE = 1005;
const int MAX_T = 105;
int N, M, T, P, Q;
char field[MAX_SIZE][MAX_SIZE];
char patterns[MAX_T][MAX_SIZE][MAX_SIZE];
ull hash[MAX_SIZE][MAX_SIZE], tmp[MAX_SIZE][MAX_SIZE];

void computeHash(char a[MAX_SIZE][MAX_SIZE], int n, int m) {
    const ull B1 = 9973;
    const ull B2 = 100000007;
    ull t1 = 1;
    for (int j = 0; j < Q; j++)
        t1 *= B1;
    for (int i = 0; i < n; i++) {
        ull e = 0;
        for (int j = 0; j < Q; j++)
            e = e * B1 + a[i][j];
        for (int j = 0; j + Q <= m; j++) {
            tmp[i][j] = e;
            if (j + Q < m)
                e = e * B1 - t1 * a[i][j] + a[i][j + Q];
        }
    }
    ull t2 = 1;
    for (int i = 0; i < P; i++)
        t2 *= B2;
    for (int j = 0; j + Q <= m; j++) {
        ull e = 0;
        for (int i = 0; i < P; i++)
            e = e * B2 + tmp[i][j];
        for (int i = 0; i + P <= n; i++) {
            hash[i][j] = e;
            if (i + P < n)
                e = e * B2 - t2 * tmp[i][j] + tmp[i + P][j];
        }
    }
}

#include <set>

int solve() {
    std::multiset<ull> unseen;
    for (int k = 0; k < T; k++) {
        computeHash(patterns[k], P, Q);
        unseen.insert(hash[0][0]);
    }

    computeHash(field, N, M);
    for (int i = 0; i + P <= N; i++) {
        for (int j = 0; j + Q <= M; j++) {
            unseen.erase(hash[i][j]);
        }
    }
    int ans = T - unseen.size();
    return ans;
}

int main() {
    int k = 0;
    while (scanf("%d%d%d%d%d", &N, &M, &T, &P, &Q), N && M && T && P && Q) {
        for (int i = 0; i < N; i++) {
            scanf("%s", field[i]);
        }
        for (int i = 0; i < T; i++) {
            for (int j = 0; j < P; j++) {
                scanf("%s", patterns[i][j]);
            }
        }
        printf("Case %d: %d\n",++k,solve());
    }
}