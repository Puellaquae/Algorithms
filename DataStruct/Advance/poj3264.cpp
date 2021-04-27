// Balanced Lineup

#include <cstdio>
#include <iostream>
using namespace std;
#ifndef INT_MAX
#    define INT_MAX 0x7fffffff
#endif
#ifndef INT_MIN
#    define INT_MIN (-INT_MAX - 1)
#endif
const int MAX_N = 1 << 17;
int n, datmin[2 * MAX_N - 1], datmax[2 * MAX_N - 1];
int nums[2000010];
void init(int k, int l, int r) {
    if (l + 1 == r) {
        datmin[k] = datmax[k] = nums[l];
        return;
    }
    int m = (l + r) / 2;
    init(k * 2 + 1, l, m);
    init(k * 2 + 2, m, r);
    datmin[k] = min(datmin[k * 2 + 1], datmin[k * 2 + 2]);
    datmax[k] = max(datmax[k * 2 + 1], datmax[k * 2 + 2]);
}

int querymin(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) {
        return INT_MAX;
    }
    if (a <= l && r <= b) {
        return datmin[k];
    } else {
        int vl = querymin(a, b, k * 2 + 1, l, (l + r) / 2);
        int vr = querymin(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(vl, vr);
    }
}
int querymax(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) {
        return INT_MIN;
    }
    if (a <= l && r <= b) {
        return datmax[k];
    } else {
        int vl = querymax(a, b, k * 2 + 1, l, (l + r) / 2);
        int vr = querymax(a, b, k * 2 + 2, (l + r) / 2, r);
        return max(vl, vr);
    }
}
int N, Q;
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }
    init(0, 0, N);
    for (int i = 0, l, r; i < Q; i++) {
        cin >> l >> r;
        cout << querymax(l - 1, r, 0, 0, N) - querymin(l - 1, r, 0, 0, N)
             << '\n';
    }
    return 0;
}