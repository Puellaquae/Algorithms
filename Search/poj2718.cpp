//Smallest Difference
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int add(vector< int > &Num, int start, int end) {
    int N = 0;
    if (Num[start] == 0) {
        return -1;
    }
    for (; start < end; start++) {
        N = N * 10 + Num[start];
    }
    return N;
}

void solve() {
    string x;
    int ans = 1e7;
    vector< int > Num;
    getline(cin, x);
    for (int i = 0; i < x.size(); i++) {
        if ('0' <= x[i] && x[i] <= '9') {
            Num.push_back(x[i] - '0');
        }
    }
    if (Num.size() == 2) {
        cout << abs(Num[0] - Num[1]) << endl;
        return;
    }
    do {
        int numA = add(Num, 0, Num.size() / 2);
        int numB = add(Num, Num.size() / 2, Num.size());
        if (numA != -1 && numB != -1) {
            int tans = abs(numA - numB);
            if (tans < ans) {
                ans = tans;
            }
        }
        numA = add(Num, 0, Num.size() / 2 + 1);
        numB = add(Num, Num.size() / 2 + 1, Num.size());
        if (numA != -1 && numB != -1) {
            int tans = abs(numA - numB);
            if (tans < ans) {
                ans = tans;
            }
        }
    } while (next_permutation(Num.begin(), Num.end()));
    cout << ans << endl;
}

int main() {
    int n;
    cin >> n;
    string ClearCin;
    getline(cin, ClearCin);
    while (n--) {
        solve();
    }
    return 0;
}