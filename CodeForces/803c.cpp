#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a, pos, neg;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x < 0) {
            neg.push_back(x);
        } else if (x > 0) {
            pos.push_back(x);
        } else if (a.size() < 2) {
            a.push_back(x);
        }
    }

    if (pos.size() > 2 || neg.size() > 2) {
        cout << "NO\n";
        return;
    }

    for (auto i : neg) {
        a.push_back(i);
    }

    for (auto i : pos) {
        a.push_back(i);
    }

    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            for (int k = j + 1; k < a.size(); k++) {
                bool ok = false;
                for (int l = 0; l < a.size(); l++) {
                    ok |= (a[i] + a[j] + a[k] == a[l]);
                }    
                if (!ok) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    cout << "YES\n";
}

int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        solve();
    }
}