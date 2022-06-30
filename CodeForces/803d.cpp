#include <iostream>
#include <vector>
using namespace std;

bool in(int l, int r) {
    cout << "? " << l << " " << r << endl;
    int n;
    int inP = 0;
    for (int i = l; i <= r; i++) {
        cin >> n;
        inP += (l <= n && n <= r);
    }
    return inP % 2 != 0;
}

void solve() {
    int n;
    cin >> n;
    int l = 1;
    int r = n;
    while (r > l) {
        int mid = (r + l) / 2;
        if (in(l, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << "! " << r << endl;
}

int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        solve();
    }
}