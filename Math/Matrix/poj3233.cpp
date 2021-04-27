// Matrix Power Series

#include <cstdio>
#include <iostream>
#include <vector>
typedef long long i64;
using namespace std;
i64 mod;
typedef vector<i64> vec;
typedef vector<vec> mat;

template <typename T>
vector<vector<T> > mul(vector<vector<T> > &A, vector<vector<T> > &B) {
    vector<vector<T> > C(A.size(), vector<T>(B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int k = 0; k < B.size(); k++) {
            if (A[i][k] != 0) {
                for (int j = 0; j < B[0].size(); j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
                }
            }
        }
    }
    return C;
}
template <typename T> vector<vector<T> > pow(vector<vector<T> > &A, i64 n) {
    vector<vector<T> > B(A.size(), vector<T>(A.size()));
    for (int i = 0; i < A.size(); i++) {
        B[i][i] = 1;
    }
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
    int n, k;
    cin >> n >> k >> mod;
    mat A(n * 2, vec(n * 2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = n; i < 2 * n; i++) {
        A[i][i] = 1;
        A[i - n][i] = 1;
    }
    A = pow(A, k + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (A[i][j + n] - (i == j ? 1 : 0)) % mod << " ";
        }
        cout << "\n";
    }
}