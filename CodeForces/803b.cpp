#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (k == 1) {
        cout << (n + 1) / 2 - 1 << "\n";
        return; 
    }
    int c = 0;
    for (int i = 1; i < n - 1; i++) {
        if (a[i - 1] + a[i + 1] < a[i]) {
            c++;
        }
    }
    cout << c << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        solve();
    }
}