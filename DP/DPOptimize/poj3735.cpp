// Training little cats

#include <cstdio>
#include <iostream>
#include <vector>
typedef long long i64;
using namespace std;
typedef vector<i64> vec;
typedef vector<vec> mat;
mat mul(mat &A, mat &B) {
    mat C(A.size(), vec(B[0].size()));
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
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k) && !(n == 0 && m == 0 && k == 0)) {
        mat A(n + 1, vec(n + 1));
        for (int i = 0; i <= n; i++) {
            A[i][i] = 1;
        }
        for (int ii = 0; ii < k; ii++) {
            char op;
            getchar();
            op = getchar();
            if (op == 'g') {
                int i;
                scanf("%d", &i);
                A[0][i]++;
            } else if (op == 'e') {
                int i;
                scanf("%d", &i);
                for (int t = 0; t <= n; t++) {
                    A[t][i] = 0;
                }
            } else if (op == 's') {
                int i, j;
                scanf("%d%d", &i, &j);
                for (int t = 0; t <= n; t++) {
                    swap(A[t][i], A[t][j]);
                }
            }
        }
        mat B(1, vec(n + 1));
        B[0][0] = 1;
        A = pow(A, m);
        mat C = mul(B, A);
        for (int i = 1; i <= n; i++) {
            printf("%lld ", C[0][i]);
        }
        printf("\n");
    }
}