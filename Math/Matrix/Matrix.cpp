#include <cstdio>
#include <iostream>
#include <vector>
typedef long long i64;
using namespace std;

typedef vector<i64> vec;
typedef vector<vec> mat;

template <typename T>
vector<vector<T> > mul(vector<vector<T> > &A, vector<vector<T> > &B) {
    vector<vector<T> > C(A.size(), vector<T>(B[0].size()));
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