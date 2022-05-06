#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int maxk = a[i] / x;
        int usedk = min(k, maxk);
        k -= usedk;
        a[i] -= x * usedk;
    }
    if (k > 0) {
        sort(a.begin(), a.end(), greater<>());
        for (int i = 0; i < n && k > 0; i++, k--) {
            a[i] = 0;
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i];
    }
    cout << ans << endl;
    return 0;
}