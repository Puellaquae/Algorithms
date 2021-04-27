// Numerical Sequence(hard)
#include <iostream>
using namespace std;
typedef long long i64;
i64 sum(i64 r, int need) {
    i64 pw = 1, sum = 0, add = 0;
    for (int len = 1;; len++) {
        if (pw * 10 - 1 < r) {
            i64 cnt = pw * 10 - pw;
            if (need) {
                sum += add * cnt + (cnt + 1) * cnt / 2 * len;
                add += cnt * len;
            } else {
                sum += cnt * len;
            }
        } else {
            i64 cnt = r - pw + 1;
            if (need) {
                sum += add * cnt + (cnt + 1) * cnt / 2 * len;
            } else {
                sum += cnt * len;
            }
            break;
        }
        pw *= 10;
    }
    return sum;
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        i64 k;
        cin >> k;
        k--;
        i64 l = 1, r = 1e9;
        i64 res = -1;
        while (r - l >= 0) {
            i64 mid = (l + r) >> 1;
            if (sum(mid, 1) > k) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        k -= sum(res - 1, 1);
        l = 1, r = res;
        i64 num = -1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (sum(mid, 0) > k) {
                num = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << to_string(num)[k - sum(num - 1, 0)] << endl;
    }
    return 0;
}