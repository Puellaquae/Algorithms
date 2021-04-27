// Saruman's Army
// Using Greedy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void solve(int N, int R) {
    vector<int> X(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }
    sort(X.begin(), X.end());
    int i = 0, ans = 0;
    while (i < N) {
        int s = X[i++];
        while (i < N && X[i] <= s + R)
            i++;
        int p = X[i - 1];
        while (i < N && X[i] <= p + R)
            i++;
        ans++;
    }
    cout << ans << endl;
}
int main() {
    int N, R;
    while (cin >> R >> N && N != -1 && R != -1) {
        solve(N, R);
    }
}