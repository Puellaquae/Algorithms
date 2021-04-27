// Crane

#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int ST_SIZE = (1 << 15) - 1;
const int MAX_N = 10000 + 10;
const int MAX_C = 10000 + 10;
const double PI = 3.1415926535897932; // 384626433832795;
int N, C;
int L[MAX_N];
int S[MAX_C], A[MAX_N];
double vx[ST_SIZE], vy[ST_SIZE];
double ang[ST_SIZE];
double prv[MAX_N];
void init(int k, int l, int r) {
    ang[k] = vx[k] = 0.0;
    if (r - l == 1) {
        vy[k] = L[l];
    } else {
        int chl = k * 2 + 1, chr = k * 2 + 2;
        init(chl, l, (l + r) / 2);
        init(chr, (l + r) / 2, r);
        vy[k] = vy[chl] + vy[chr];
    }
}
void change(int s, double a, int v, int l, int r) {
    if (s <= l) {
        return;
    } else if (s < r) {
        int chl = v * 2 + 1, chr = v * 2 + 2;
        int m = (l + r) / 2;
        change(s, a, chl, l, m);
        change(s, a, chr, m, r);
        if (s <= m) {
            ang[v] += a;
        }

        double ss = sin(ang[v]), c = cos(ang[v]);
        vx[v] = vx[chl] + (c * vx[chr] - ss * vy[chr]);
        vy[v] = vy[chl] + (ss * vx[chr] + c * vy[chr]);
    }
}
void solve() {
    init(0, 0, N);
    for (int i = 0; i < N; i++) {
        prv[i] = PI;
    }
    for (int i = 0; i < C; i++) {
        int s = S[i];
        double a = A[i] / 360.0 * 2 * PI;
        change(s, a - prv[s], 0, 0, N);
        prv[s] = a;
        printf("%.2f %.2f\n", vx[0], vy[0]);
    }
}
int main() {
    while (cin >> N >> C) {
        for (int i = 0; i < N; i++) {
            cin >> L[i];
        }
        for (int i = 0; i < C; i++) {
            cin >> S[i] >> A[i];
        }
        solve();
    }
}