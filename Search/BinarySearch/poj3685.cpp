// Matrix
#include <iostream>
using namespace std;
typedef long long int64;
const int64 INF = 0x7fffffffffffffff;
const int MAX_N = 1e5 + 10;
int64 a[MAX_N], N, M;
int64 f(int64 x, int64 y) { return x * x + 100000 * x + y * y - 100000 * y + x * y; }
bool C(int64 mid) {
    int64 ans = 0;
    for (int j = 1; j <= N; j++) {
        int64 l = 1, r = N, smaller = 0;
        while (l <= r) {
            int64 mid2 = (l + r) / 2;
            if (f(mid2, j) <= mid) {
                smaller = mid2;
                l = mid2 + 1;
            } else {
                r = mid2 - 1;
            }
        }
        ans += smaller;
    }
    return ans >= M;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        int64 l = -INF, r = INF, ans;
        while (l <= r) {
            int64 mid = (l + r) / 2;
            if (C(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}