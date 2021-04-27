// Cow Bowing
// Using DP
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<vector<int> > tw(n, vector<int>(n));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            cin >> tw[i - 1][j];
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < i + 1; j++) {
            tw[i][j] += max(tw[i + 1][j], tw[i + 1][j + 1]);
        }
    }
    cout << tw[0][0] << endl;
}