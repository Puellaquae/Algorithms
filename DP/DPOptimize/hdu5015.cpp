// 233 Matrix
#include <cstdio>
#include <iostream>
#include <vector>
typedef long long i64;
using namespace std;
typedef vector<i64> vec;
typedef vector<vec> mat;
int M = 10000007;
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
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        mat A(n + 2, vec(n + 2));
        for (int i = 0; i <= n; i++) {
            A[i][0] = 10;
        }
        for (int i = 0; i <= n + 1; i++) {
            A[i][n + 1] = 1;
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                A[i][j] = 1;
            }
        }
        mat B(n + 2, vec(1));
        B[0][0] = 23;
        for (int i = 1, x; i <= n; i++) {
            scanf("%d", &x);
            B[i][0] = x;
        }
        B[n + 1][0] = 3;
        A = pow(A, m);
        mat C = mul(A, B);
        printf("%lld\n", C[n][0]);
    }
}