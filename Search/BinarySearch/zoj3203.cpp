// Light Bulb

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
const double E = 1e-7;
double f(double k, double D, double H, double h) {
    double L = h * k / (H - h);
    if (L + k > D) {
        double LinWall = L + k - D;
        L = L - LinWall + H * LinWall / (k + L);
    }
    return L;
}

void solve() {
    double H, h, D;
    cin >> H >> h >> D;
    double l = 0, r = D;
    while (r - l >= E) {
        double m1 = l + (r - l) / 3.0, m2 = r - (r - l) / 3.0;
        if (f(m1, D, H, h) < f(m2, D, H, h)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    cout << fixed << setprecision(3) << f(l, D, H, h) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}