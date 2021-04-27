// Drying
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long int64;
const int64 MAX_N = 1e6 + 5;
int64 A[MAX_N];
int64 N, K;
bool C(int64 X) {
    int64 time = 0;
    for (int64 i = 0; i < N; i++) {
        if (A[i] > X) {
            time += (A[i] - X + K - 2) / (K - 1);
        }
    }
    return time > X;
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    while (cin >> N) {
        int64 lb = 1, ub = 0;
        for (int64 i = 0; i < N; i++) {
            cin >> A[i];
            ub = ub > A[i] ? ub : A[i];
        }
        cin >> K;
        if (K == 1) {
            cout << ub << endl;
            continue;
        }
        while (lb <= ub) {
            int64 mid = (lb + ub) / 2;
            if (C(mid)) {
                lb = mid + 1;
            } else {
                ub = mid - 1;
            }
        }
        cout << lb << endl;
    }
}