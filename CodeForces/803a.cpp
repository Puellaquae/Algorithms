#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int r;
    for (int i = 0; i < n; i++) {
        cin >> r;
    }
    cout << r << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        solve();
    }
}