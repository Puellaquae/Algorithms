#include <iostream>
using namespace std;

int64_t calc(int ia, int ib) {
    int64_t a = ia, b = ib;
    return a * a * a + a * a * b + a * b * b + b * b * b;
}

int main() {
    int64_t n;
    cin >> n;
    int a = 0, b = 1000000;
    int64_t res = INT64_MAX;
    for (; a <= 1000000 && a <= b; a++) {
        for (; a <= b && calc(a, b) >= n; b--) {
            res = min(res, calc(a, b));
        }
    }
    cout << res << endl;
    return 0;
}