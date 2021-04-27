// River Hopscotch

#include <algorithm>
#include <iostream>
const int MAX_N = 5e4 + 5;
using namespace std;
int L, N, M;
int D[MAX_N];
bool C(int x) {
    int Count = 0;
    int Prev = 0;
    for (int i = 1; i < N + 1; i++) {
        if (D[i] - D[Prev] < x) {
            Count++;
        } else {
            Prev = i;
        }
    }
    if (D[N + 1] - D[Prev] < x) {
        Count++;
    }
    return Count <= M;
}
int main() {
    cin >> L >> N >> M;
    D[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> D[i];
    }
    D[N + 1] = L;
    sort(D + 1, D + N + 1);
    if (C(L)) {
        cout << L << endl;
        return 0;
    }
    int lb = 0, ub = L;
    while (lb < ub - 1) {
        int mid = (lb + ub) / 2;
        if (C(mid)) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    cout << lb << endl;
    return 0;
}