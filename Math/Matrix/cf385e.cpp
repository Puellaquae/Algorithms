//Bear in the Field
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
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j] % mod) % mod;
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
    i64 n, sx, sy, dx, dy, t;
    cin >> n >> sx >> sy >> dx >> dy >> t;
    mod = n;
    mat A(6, vec(6));
    A = {{2, 1, 1, 0, 1, 0}, {1, 2, 0, 1, 1, 0}, {1, 1, 1, 0, 1, 0},
         {1, 1, 0, 1, 1, 0}, {0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 1}};
    mat B(6, vec(1));
    B = {{sx}, {sy}, {(dx % n) + n}, {(dy % n) + n}, {0}, {1}};
    A = pow(A, t);
    B = mul(A, B);
    cout << (B[0][0] == 0 ? n : B[0][0]) << " " << (B[1][0] == 0 ? n : B[1][0])
         << endl;
}