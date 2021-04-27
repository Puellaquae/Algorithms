// Monthly Expense
#include <iostream>
using namespace std;
const int MAX_N = 1e6 * 5;
int N, M;
int S[MAX_N];
bool C(int X) {
    int Count = 0;
    int temp = 1;
    for (int i = 0; i < N; i++) {
        if (temp + S[i] <= X) {
            temp += S[i];
        } else {
            temp = S[i];
            Count++;
        }
    }
    return Count >= M;
}

int main() {
    while (cin >> N >> M) {
        int lb = 0, ub = 0;
        for (int i = 0; i < N; i++) {
            cin >> S[i];
            ub += S[i];
            lb = lb < S[i] ? S[i] : lb;
        }

        while (lb < ub) {
            int mid = (lb + ub) / 2;
            if (C(mid)) {
                lb = mid + 1;
            } else {
                ub = mid - 1;
            }
        }
        cout << ub << endl;
    }
    return 0;
}