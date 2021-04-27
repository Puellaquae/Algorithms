// Secretary

#include <algorithm>
#include <iostream>
#include <string>

const int MAX_N = 10050;

int n, k;
int rank[MAX_N + 1];
int tmp[MAX_N + 1];
bool compare_sa(int i, int j) {
    if (rank[i] != rank[j])
        return rank[i] < rank[j];
    else {
        int ri = i + k <= n ? rank[i + k] : -1;
        int rj = j + k <= n ? rank[j + k] : -1;
        return ri < rj;
    }
}
void construct_sa(std::string S, int *sa) {
    n = S.size();
    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rank[i] = i < n ? S[i] : -1;
    }
    for (k = 1; k <= n; k *= 2) {
        std::sort(sa, sa + n + 1, compare_sa);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] =
                tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= n; i++) {
            rank[i] = tmp[i];
        }
    }
}

void construct_lcp(std::string S, int *sa, int *lcp) {
    int n = S.size();
    for (int i = 0; i <= n; i++)
        rank[sa[i]] = i;
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
        int j = sa[rank[i] - 1];
        if (h > 0)
            h--;
        for (; j + h < n && i + h < n; h++) {
            if (S[j + h] != S[i + h])
                break;
        }
        lcp[rank[i] - 1] = h;
    }
}
using namespace std;
const int MAX_L = 10050;
string S, T;
int sa[MAX_L], lcp[MAX_L];
void solve() {
    int s1 = S.size();
    S += '\0' + T;
    construct_sa(S, sa);
    construct_lcp(S, sa, lcp);
    int ans = 0;
    for (int i = 0; i < S.size(); i++) {
        if ((sa[i] < s1) != (sa[i + 1] < s1)) {
            ans = max(ans, lcp[i]);
        }
    }
    printf("Nejdelsi spolecny retezec ma delku %d.\n", ans);
}

int main() {
    int t;
    cin >> t;
    getchar();
    while (t--) {
        getline(cin, S);
        getline(cin, T);
        solve();
    }
}