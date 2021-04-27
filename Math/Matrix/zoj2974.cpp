// Just Pour the Water

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<double> vec;
typedef vector<vec> mat;

template <typename T>
vector<vector<T>> mul(vector<vector<T>> &A, vector<vector<T>> &B) {
    vector<vector<T>> C(A.size(), vector<T>(B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int k = 0; k < B.size(); k++) {
            if (A[i][k] != 0) {
                for (int j = 0; j < B[0].size(); j++) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }
            }
        }
    }
    return C;
}
template <typename T>
vector<vector<T>> pow(vector<vector<T>> &A, vector<vector<T>> &B, int n) {
    while (n > 0) {
        if (n & 1) {
            B = mul(B, A);
        }
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}

int main() {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        mat I(n, vec(n, 0));
        mat U(n, vec(n, 0));
        for (int i = 0; i < n; i++)
            cin >> I[0][i];
        for (int i = 0, tmp, xh; i < n; i++) {
            cin >> tmp;
            if (tmp == 0)
                U[i][i] = 1;
            else {
                for (int j = 0; j < tmp; j++) {
                    cin >> xh;
                    U[i][xh - 1] += 1. / tmp;
                }
            }
        }
        int time;
        cin >> time;
        mat res = pow(U, I, time);
        for (int i = 0; i < n; i++) {
            printf("%.2f", res[0][i]);
            printf(i == n - 1 ? "\n" : " ");
        }
    }
}