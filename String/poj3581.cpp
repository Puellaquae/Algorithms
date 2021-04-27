// Sequence

#include <cstdio>
const int MAX_N = 200005;
int N, A[MAX_N], n, k;
int rev[MAX_N * 2], sa[MAX_N * 2];
int rank[MAX_N + 1], tmp[MAX_N + 1];
bool compareSA(int i, int j) {
    if (rank[i] != rank[j]) {
        return rank[i] < rank[j];
    } else {
        int ri = i + k <= n ? rank[i + k] : -1;
        int rj = j + k <= n ? rank[j + k] : -1;
        return ri < rj;
    }
}
#include <algorithm>
void constructSA(int *s, int len, int *sa) {
    n = len;
    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rank[i] = i < n ? s[i] : -1;
    }
    for (k = 1; k <= n; k *= 2) {
        std::sort(sa, sa + n + 1, compareSA);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compareSA(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= n; i++) {
            rank[i] = tmp[i];
        }
    }
}
void solve() {
    std::reverse_copy(A, A + N, rev);
    constructSA(rev, N, sa);
    int p1;
    for (int i = 0; i < N; i++) {
        p1 = N - sa[i];
        if (p1 >= 1 && N - p1 >= 2)
            break;
    }
    int m = N - p1;
    std::reverse_copy(A + p1, A + N, rev);
    std::reverse_copy(A + p1, A + N, rev + m);
    constructSA(rev, m * 2, sa);
    int p2;
    for (int i = 0; i <= 2 * m; i++) {
        p2 = p1 + m - sa[i];
        if (p2 - p1 >= 1 && N - p2 >= 1)
            break;
    }
    std::reverse(A, A + p1);
    std::reverse(A + p1, A + p2);
    std::reverse(A + p2, A + N);
    for (int i = 0; i < N; i++) {
        printf("%d\n", A[i]);
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", A + i);
    }
    solve();
}