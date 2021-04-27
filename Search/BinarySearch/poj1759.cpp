// Garland
#include <iomanip>
#include <iostream>
using namespace std;
int N;
double H[1050], B;
bool C(double h2) {
    H[2] = h2;
    for (int i = 3; i <= N; i++) {
        H[i] = 2 * H[i - 1] + 2 - H[i - 2];
        if (H[i] < 0) {
            return false;
        }
    }
    B = H[N];
    return true;
}
int main() {
    cin >> N >> H[1];
    double l = -1, r = 1016, mid;
    while ((r - l) > 1e-7) {
        mid = (l + r) / 2;
        if (C(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(2) << B << endl;
    return 0;
}