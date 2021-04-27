// Tr A
#include <cstdio>
#include <iostream>
#include <vector>
typedef long long i64;
using namespace std;
typedef vector<i64> vec;
typedef vector<vec> mat;
const int mod = 9973;
mat mul(mat &A, mat &B) {
    mat C(A.size(), vec(B[0].size()));
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
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        mat a(n, vec(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
        a = pow(a, m);
        i64 ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + a[i][i]) % mod;
        }
        ans %= mod;
        cout << ans << endl;
    }
}