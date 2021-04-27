// Evolution

#include <cstdio>
#include <iostream>
#include <vector>
typedef long long i64;
using namespace std;

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

int main() {
    typedef vector<double> vec;
    typedef vector<vec> mat;
    int n, m;
    while (cin >> n >> m && (n || m)) {
        mat P(n, vec(1));
        mat H(n, vec(n, 0.0));
        for (int i = 0; i < n; i++) {
            cin >> P[i][0];
        }
        int k;
        cin >> k;
        while (k--) {
            int i, j;
            double p;
            cin >> i >> j >> p;
            H[i][j] = p;
        }
        for (int i = 0; i < n; i++) {
            double pp = 1.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    pp -= H[i][j];
                }
            }
            H[i][i] = pp;
        }
        H = pow(H, m);
        double ans = 0.0;
        for (int i = 0; i < n; i++) {
            ans += H[i][n - 1] * P[i][0];
        }
        printf("%.0f\n", ans);
    }
}