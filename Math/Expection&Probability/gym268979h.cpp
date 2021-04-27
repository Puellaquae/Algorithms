// Touching Fish

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<double> dp1(n + 1), dp2(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        dp1[i] = dp1[i + 1] + 1.0 * n / (n - i);
        dp2[i] = 1.0 * i / (n - i) * (2.0 * dp1[i] + 1.0) + dp2[i + 1] + 2.0 *
                dp1[i + 1] + 1.0;
    }
    cout << fixed << setprecision(12) << 0.5 * (dp1[0] + dp2[0]);
    return 0;
}