// Glass Breads

#include <algorithm>
#include <iostream>
#include <string>
const int MAX_N = 20010;
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
    int _n = S.size();
    for (int i = 0; i <= _n; i++)
        rank[sa[i]] = i;
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < _n; i++) {
        int j = sa[rank[i] - 1];
        if (h > 0)
            h--;
        for (; j + h < _n && i + h < _n; h++) {
            if (S[j + h] != S[i + h])
                break;
        }
        lcp[rank[i] - 1] = h;
    }
}
using namespace std;
int sa[MAX_N], lcp[MAX_N];
string s;
void solve() {
    int l = s.size();
    s = s + s;
    construct_sa(s, sa);
    construct_lcp(s, sa, lcp);
    int ans = 0;
    for (int i = 0; i <= s.size(); i++) {
        if (sa[i] < l) {
            ans = sa[i] + 1;
            while (i + 1 <= s.size() && lcp[i] >= l) {
                ans = min(ans, sa[i + 1] + 1);
                i++;
            }
            printf("%d\n", ans);
            break;
        }
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        solve();
    }
}