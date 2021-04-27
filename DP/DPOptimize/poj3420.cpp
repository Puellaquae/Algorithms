// Quad Tiling

#include <cstdio>
#include <iostream>
#include <vector>
typedef long long i64;
using namespace std;
typedef vector<i64> vec;
typedef vector<vec> mat;
int M;
mat mul(mat &A, mat &B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int k = 0; k < B.size(); k++) {
            for (int j = 0; j < B[0].size(); j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
            }
        }
    }
    return C;
}
mat pow(mat &A, i64 n) {
    mat B(A.size(), vec(A.size()));
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
    mat B(4, vec(1));
    B[0][0] = 36;
    B[1][0] = 11;
    B[2][0] = 5;
    B[3][0] = 1;
    int n;
    while (~scanf("%d%d", &n, &M) && n && M) {
        if (n == 1) {
            printf("%d\n", 1 % M);
        } else if (n == 2) {
            printf("%d\n", 5 % M);
        } else if (n == 3) {
            printf("%d\n", 11 % M);
        } else if (n == 4) {
            printf("%d\n", 36 % M);
        } else {
            mat A(4, vec(4));
            A[0][0] = 1;
            A[0][1] = 5;
            A[0][2] = 1;
            A[0][3] = -1;
            A[1][0] = 1;
            A[2][1] = 1;
            A[3][2] = 1;
            A = pow(A, n - 4);
            i64 ans = (A[0][0] * 36 + A[0][1] * 11 + A[0][2] * 5 + A[0][3]) % M;
            if (ans < 0) {
                ans += M;
            }
            printf("%lld\n", ans);
        }
    }
}