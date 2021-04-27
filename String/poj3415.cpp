// Common Substrings

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
const int MAX_L = 100000 + 1;
const int MAX_N = 2 * MAX_L + 1;
std::string S;
int n, k;
int sa[MAX_N + 1], lcp[MAX_N + 1];
int rank[MAX_N + 1], tmp[MAX_N + 1];

bool compare_sa(const int i, const int j) {
    if (rank[i] != rank[j]) {
        return rank[i] < rank[j];
    }
    return (i + k <= n ? rank[i + k] : -1) < (j + k <= n ? rank[j + k] : -1);
}
void construct_sa() {
    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rank[i] = i < n ? S[i] : -1;
    }

    for (k = 1; k <= n; k <<= 1) {
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

void construct_lcp() {
    memset(lcp, 0, sizeof(lcp));
    for (int i = 0; i <= n; i++) {
        rank[sa[i]] = i;
    }
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
        int j = sa[rank[i] - 1];
        if (h > 0) {
            h--;
        }
        for (; i + h < n && j + h < n && S[i + h] == S[j + h]; h++)
            ;
        lcp[rank[i] - 1] = h;
    }
}

int stack[MAX_N][2];
long long contribution, top;
using namespace std;

long long solve(int K, int l1, bool is_s1) {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (lcp[i] < K) {
            top = contribution = 0;
        } else {
            int size = 0;
            if ((is_s1 && sa[i] < l1) || (!is_s1 && sa[i] > l1)) {
                ++size;
                contribution += lcp[i] - K + 1;
            }
            while (top > 0 && lcp[i] <= stack[top - 1][0]) {
                --top;
                contribution -= stack[top][1] * (stack[top][0] - lcp[i]);
                size += stack[top][1];
            }
            if (size) {
                stack[top][0] = lcp[i];
                stack[top][1] = size;
                ++top;
            }
            if ((is_s1 && sa[i + 1] > l1) || (!is_s1 && sa[i + 1] < l1)) {
                ans += contribution;
            }
        }
    }
    return ans;
}

int main() {
    int K;
    while (scanf("%d", &K), K) {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        int l1 = s1.length(), l2 = s2.length();
        S = s1 + '$' + s2;
        n = l1 + l2 + 1;
        construct_sa();
        construct_lcp();
        printf("%lld\n", solve(K, l1, true) + solve(K, l1, false));
    }
    return 0;
}