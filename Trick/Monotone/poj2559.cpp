// Largest Rectangle in a Histogram

#include <algorithm>
#include <iostream>
using namespace std;
#define MAX_N 100005
int n;
int h[MAX_N];
int L[MAX_N], R[MAX_N];
int st[MAX_N];
void solve() {
    int t = 0;
    for (int i = 0; i < n; i++) {
        while (t > 0 && h[st[t - 1]] >= h[i])
            t--;
        L[i] = t == 0 ? 0 : (st[t - 1] + 1);
        st[t++] = i;
    }
    t = 0;
    for (int i = n - 1; i >= 0; i--) {
        while (t > 0 && h[st[t - 1]] >= h[i])
            t--;
        R[i] = t == 0 ? n : st[t - 1];
        st[t++] = i;
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, (long long)h[i] * (R[i] - L[i]));
    }
    printf("%lld\n", res);
}
int main() {
    while (~scanf("%d", &n)&&n) {
        for (int i = 0; i < n; i++) {
            scanf("%d", h + i);
        }
        solve();
    }
}