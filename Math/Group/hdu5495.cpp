// LCS
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    vector<int> ra(n + 1);
    vector<bool> check(n + 1, false);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ra[a[i]] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (a[i] == b[i]) {
            ans++;
            check[a[i]] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!check[i]) {
            bool f = false;
            int pos = i;
            while (!check[pos]) {
                check[pos] = true;
                pos = b[ra[pos]];
                if (f) {
                    ans++;
                }
                f = true;
            }
        }
    }
    cout << ans << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}